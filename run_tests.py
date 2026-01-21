#!/usr/bin/env python3
"""
Test runner for AST-based C code minifier

Runs all test files, compiles minified output, and verifies execution.
"""

import os
import subprocess
import time


def run_cmd(cmd, silent=False):
    """Run a shell command and return the result"""
    result = subprocess.run(
        cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
    )
    return result


def main():
    test_dir = "./tests"
    files = sorted([f for f in os.listdir(test_dir) if f.endswith(".c")])
    
    print(f"Found {len(files)} tests in {test_dir}\n")
    
    passed = 0
    failed = 0
    
    for f in files:
        filepath = os.path.join(test_dir, f)
        base_name = f[:-2]  # remove .c
        output_c = os.path.join(test_dir, f"{base_name}_min.c")
        
        print(f"Running test: {f}...", end=" ")
        
        # 1. Run Minifier using venv python
        cmd_minify = f"./venv/bin/python3 minify.py {filepath} > {output_c}"
        res = run_cmd(cmd_minify)
        if res.returncode != 0:
            print(f"FAILED (Minifier Error)\n{res.stderr}")
            failed += 1
            continue
        
        # 2. Compile Minified
        current_time = int(time.time())
        bin_min = os.path.join(test_dir, f"{base_name}_min_{current_time}")
        
        cmd_compile = f"gcc -o {bin_min} {output_c}"
        res_comp = run_cmd(cmd_compile)
        if res_comp.returncode != 0:
            print(f"FAILED (Minified Compilation Error)\n{res_comp.stderr}")
            failed += 1
            # Cleanup
            if os.path.exists(output_c):
                os.remove(output_c)
            continue
        
        # 3. Run Minified
        res_run = run_cmd(f"./{bin_min}")
        if res_run.returncode != 0:
            print(f"FAILED (Runtime Error: {res_run.returncode})")
            failed += 1
            if os.path.exists(bin_min):
                os.remove(bin_min)
            if os.path.exists(output_c):
                os.remove(output_c)
            continue
        
        # If we reached here, it compiles and runs.
        print("PASSED")
        # Cleanup binaries
        if os.path.exists(bin_min):
            os.remove(bin_min)
        if os.path.exists(output_c):
            os.remove(output_c)
        passed += 1
    
    print(f"\nSummary: {passed}/{len(files)} passed.")
    if failed > 0:
        exit(1)


if __name__ == "__main__":
    main()
