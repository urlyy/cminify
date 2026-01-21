#!/usr/bin/env python3
"""
AST-based C Code Minifier using tree-sitter

This tool minifies C code by:
1. Removing comments
2. Minimizing whitespace
3. Renaming local variables, function parameters, and static globals
"""

import sys
import tree_sitter_c as tsc
from tree_sitter import Language, Parser, Node

# Configuration
ENABLE_RENAMING = True

# C Keywords that should never be renamed
KEYWORDS = {
    'auto', 'break', 'case', 'char', 'const', 'continue', 'default', 'do',
    'double', 'else', 'enum', 'extern', 'float', 'for', 'goto', 'if',
    'int', 'long', 'register', 'return', 'short', 'signed', 'sizeof', 'static',
    'struct', 'switch', 'typedef', 'union', 'unsigned', 'void', 'volatile', 'while',
    # Common stdlib functions
    'main', 'printf', 'fprintf', 'sprintf', 'scanf', 'sscanf', 'fscanf',
    'malloc', 'calloc', 'realloc', 'free', 'memcpy', 'memset', 'strlen',
    'strcpy', 'strncpy', 'strcmp', 'strncmp', 'strcat', 'strncat',
    'fopen', 'fclose', 'fread', 'fwrite', 'fseek', 'ftell', 'rewind',
    'exit', 'abort', 'atexit', 'getenv', 'system',
}


def generate_short_name(index):
    """Generate short variable names: a, b, ..., z, A, ..., Z, aa, ab, ..."""
    chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    base = len(chars)
    name = ''
    while True:
        name = chars[index % base] + name
        index //= base
        if index == 0:
            break
        index -= 1
    return name


class Scope:
    """Represents a variable scope with renaming mappings"""
    def __init__(self, is_protected=False):
        self.mappings = {}  # original_name -> new_name
        self.counter = 0
        self.is_protected = is_protected  # Don't rename in struct/union/enum
        
    def add_variable(self, name):
        """Add a variable to this scope and generate a short name"""
        if name in self.mappings or name in KEYWORDS:
            return self.mappings.get(name, name)
        
        new_name = generate_short_name(self.counter)
        while new_name in KEYWORDS:
            self.counter += 1
            new_name = generate_short_name(self.counter)
        
        self.counter += 1
        self.mappings[name] = new_name
        return new_name
    
    def get_mapping(self, name):
        """Get the renamed version of a variable"""
        return self.mappings.get(name)


class CMinifier:
    def __init__(self, source_code):
        self.source = source_code
        self.source_bytes = source_code.encode('utf-8')
        
        # Initialize tree-sitter
        self.language = Language(tsc.language())
        self.parser = Parser(self.language)
        self.tree = self.parser.parse(self.source_bytes)
        
        # Scope management
        self.scopes = [Scope()]  # Global scope
        self.current_scope_idx = 0
        
        # Track what to keep/remove
        self.removals = []  # List of (start_byte, end_byte) to remove
        self.replacements = {}  # byte_offset -> new_text
        
    def get_node_text(self, node):
        """Get the text content of a node"""
        return self.source_bytes[node.start_byte:node.end_byte].decode('utf-8')
    
    def is_comment(self, node):
        """Check if node is a comment"""
        return node.type == 'comment'
    
    def is_struct_union_enum_specifier(self, node):
        """Check if we're in a struct/union/enum definition"""
        if node.type in ('struct_specifier', 'union_specifier', 'enum_specifier'):
            return True
        if node.parent:
            return self.is_struct_union_enum_specifier(node.parent)
        return False
    
    def find_comments(self, node):
        """Recursively find all comments in the AST"""
        if self.is_comment(node):
            self.removals.append((node.start_byte, node.end_byte))
        
        for child in node.children:
            self.find_comments(child)
    
    def is_declaration(self, node):
        """Check if an identifier is part of a declaration"""
        if not node.parent:
            return False
        
        parent = node.parent
        
        # Direct declarator in a declaration
        if parent.type == 'init_declarator':
            return True
        if parent.type == 'declarator':
            # Check if this declarator is part of a declaration
            p = parent.parent
            while p:
                if p.type in ('declaration', 'parameter_declaration', 'field_declaration'):
                    return True
                p = p.parent
        
        # Parameter declaration
        if parent.type == 'parameter_declaration':
            return True
            
        # Field declaration (struct member)
        if parent.type == 'field_declaration':
            return True
        
        return False
    
    def is_member_access(self, node):
        """Check if identifier is a struct/union member access"""
        if not node.parent:
            return False
        
        parent = node.parent
        
        # Check for . or -> access
        if parent.type == 'field_expression':
            # node.field is the member being accessed
            if parent.child_by_field_name('field') == node:
                return True
        
        return False
    
    def is_static_global(self, node):
        """Check if this is a static global variable declaration"""
        if not self.is_declaration(node):
            return False
        
        # Walk up to find the declaration
        p = node.parent
        while p and p.type not in ('declaration', 'function_definition'):
            p = p.parent
        
        if not p or p.type != 'declaration':
            return False
        
        # Check if declaration has 'static' storage class
        for child in p.children:
            if child.type == 'storage_class_specifier' and self.get_node_text(child) == 'static':
                # Make sure we're at global scope (parent is translation_unit)
                if p.parent and p.parent.type == 'translation_unit':
                    return True
        
        return False
    
    def get_scope_depth(self, node):
        """Calculate the scope depth of a node"""
        depth = 0
        p = node.parent
        while p:
            if p.type == 'compound_statement':
                depth += 1
            p = p.parent
        return depth
    
    def analyze_identifiers(self, node, in_function=False):
        """Analyze and rename identifiers based on scope"""
        if node.type == 'identifier':
            name = self.get_node_text(node)
            
            # Skip keywords
            if name in KEYWORDS:
                return
            
            # Skip member access
            if self.is_member_access(node):
                return
            
            # Skip if in struct/union/enum definition
            if self.is_struct_union_enum_specifier(node):
                return
            
            is_decl = self.is_declaration(node)
            
            # Handle different cases
            if is_decl:
                # Static global variable
                if self.is_static_global(node):
                    new_name = self.scopes[0].add_variable(name)
                    self.replacements[node.start_byte] = (node.end_byte, new_name)
                
                # Local variable or parameter
                elif in_function and self.current_scope_idx > 0:
                    scope = self.scopes[self.current_scope_idx]
                    if not scope.is_protected:
                        new_name = scope.add_variable(name)
                        self.replacements[node.start_byte] = (node.end_byte, new_name)
            else:
                # Usage - look up in scopes from current to global
                for i in range(self.current_scope_idx, -1, -1):
                    new_name = self.scopes[i].get_mapping(name)
                    if new_name:
                        self.replacements[node.start_byte] = (node.end_byte, new_name)
                        break
        
        # Handle scope changes
        if node.type == 'compound_statement':
            # Enter new scope
            self.scopes.append(Scope())
            self.current_scope_idx += 1
            
            for child in node.children:
                self.analyze_identifiers(child, in_function=True)
            
            # Exit scope
            self.scopes.pop()
            self.current_scope_idx -= 1
        
        elif node.type == 'function_definition':
            # Function definition creates a new scope for parameters and body
            self.scopes.append(Scope())
            self.current_scope_idx += 1
            
            for child in node.children:
                self.analyze_identifiers(child, in_function=True)
            
            self.scopes.pop()
            self.current_scope_idx -= 1
        
        elif node.type in ('struct_specifier', 'union_specifier', 'enum_specifier'):
            # Protected scope - don't rename members
            self.scopes.append(Scope(is_protected=True))
            self.current_scope_idx += 1
            
            for child in node.children:
                self.analyze_identifiers(child, in_function)
            
            self.scopes.pop()
            self.current_scope_idx -= 1
        
        else:
            for child in node.children:
                self.analyze_identifiers(child, in_function)
    
    def reconstruct(self):
        """Reconstruct the source code with removals and replacements"""
        # Sort removals and replacements by position
        self.removals.sort()
        
        result = []
        pos = 0
        
        # Create a list of all modifications sorted by position
        modifications = []
        
        # Add removals
        for start, end in self.removals:
            modifications.append(('remove', start, end, None))
        
        # Add replacements
        for start, (end, text) in self.replacements.items():
            modifications.append(('replace', start, end, text))
        
        modifications.sort(key=lambda x: x[1])
        
        # Apply modifications
        for mod_type, start, end, text in modifications:
            if start > pos:
                result.append(self.source_bytes[pos:start].decode('utf-8'))
            
            if mod_type == 'replace':
                result.append(text)
            # For 'remove', we just skip the content
            
            pos = end
        
        # Add remaining content
        if pos < len(self.source_bytes):
            result.append(self.source_bytes[pos:].decode('utf-8'))
        
        return ''.join(result)
    
    def minimize_whitespace(self, code):
        """Minimize whitespace while preserving necessary spaces"""
        result = []
        i = 0
        n = len(code)
        
        while i < n:
            c = code[i]
            
            # Handle preprocessor directives - keep them on their own line
            if c == '#':
                # Keep the newline before if there is one
                if result and result[-1] != '\n':
                    result.append('\n')
                
                # Copy the entire directive
                while i < n and code[i] != '\n':
                    result.append(code[i])
                    i += 1
                if i < n:
                    result.append('\n')
                    i += 1
                continue
            
            # Handle strings and chars - preserve them exactly
            if c in ('"', "'"):
                quote = c
                result.append(c)
                i += 1
                while i < n:
                    if code[i] == '\\':
                        result.append(code[i])
                        i += 1
                        if i < n:
                            result.append(code[i])
                            i += 1
                    elif code[i] == quote:
                        result.append(code[i])
                        i += 1
                        break
                    else:
                        result.append(code[i])
                        i += 1
                continue
            
            # Handle whitespace
            if c.isspace():
                # Skip all consecutive whitespace
                while i < n and code[i].isspace():
                    i += 1
                
                # Determine if we need a space
                if result:
                    prev = result[-1]
                    if i < n:
                        next_c = code[i]
                        
                        # Need space between alphanumeric/underscore characters
                        if (prev.isalnum() or prev == '_') and (next_c.isalnum() or next_c == '_'):
                            result.append(' ')
                        # Avoid ++ or -- ambiguity
                        elif prev == '+' and next_c == '+':
                            result.append(' ')
                        elif prev == '-' and next_c == '-':
                            result.append(' ')
                continue
            
            result.append(c)
            i += 1
        
        return ''.join(result)
    
    def minify(self):
        """Main minification process"""
        # Step 1: Remove comments
        self.find_comments(self.tree.root_node)
        
        # Step 2: Rename variables if enabled
        if ENABLE_RENAMING:
            self.analyze_identifiers(self.tree.root_node)
        
        # Step 3: Reconstruct code
        code = self.reconstruct()
        
        # Step 4: Minimize whitespace
        code = self.minimize_whitespace(code)
        
        return code


def main():
    if len(sys.argv) < 2:
        print("Usage: python3 minify.py <file.c>")
        sys.exit(1)
    
    with open(sys.argv[1], 'r') as f:
        source = f.read()
    
    minifier = CMinifier(source)
    minified = minifier.minify()
    print(minified)


if __name__ == '__main__':
    main()
