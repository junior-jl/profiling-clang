## Profiling Clang

The following [code](./test.cpp) was used in the tests:


```cpp
#include <iostream>

// Compile-time constant
constexpr int kArraySize = 20;

// Function prototype for Fibonacci sequence calculation
inline int fibonacci(int n);

// Function overloading for array manipulation
void manipulateArray(int arr[], int size);
void manipulateArray(double arr[], int size);

int main() {
	// Run-time constant
	const int kFibonacciNumber = 10;

	// Fibonacci sequence using recursion
	int fibRecursive = fibonacci(kFibonacciNumber);
	std::cout << "Fibonacci Recursive(" << kFibonacciNumber << "): " << fibRecursive << std::endl;

	// Array manipulation using function overloading
	int intArray[kArraySize] = {1, 2, 3, 4, 5};
	manipulateArray(intArray, kArraySize);

	double doubleArray[kArraySize] = {1.1, 2.2, 3.3, 4.4, 5.5};
	manipulateArray(doubleArray, kArraySize);

	return 0;
}

// Fibonacci sequence using recursion
inline int fibonacci(int n) {
	return (n <= 1) ? n : (fibonacci(n - 1) + fibonacci(n - 2));
}

// Array manipulation using function overloading
void manipulateArray(int arr[], int size) {
	std::cout << "Manipulating int array: ";
	for (int i = 0; i < size; ++i) {
    	arr[i] *= 2;
    	std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void manipulateArray(double arr[], int size) {
	std::cout << "Manipulating double array: ";
	for (int i = 0; i < size; ++i) {
    	arr[i] *= 1.5;
    	std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}
```



### Clang option -ftime-report

It prints time summaries for each stage of the compilation process.

**Example 1 (Generate LLVM IR using <code>-S -emit-llvm</code>):**


```bash
$ sudo ~/lldb/LLDB/bin/clang++ -ftime-report -S -emit-llvm test.cpp
```


**Output:**


```bash
===-------------------------------------------------------------------------===
                      	Pass execution timing report
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0036 seconds (0.0036 wall clock)

   ---User Time---   --User+System--   ---Wall Time---  --- Name ---
   0.0020 ( 54.7%)   0.0020 ( 54.7%)   0.0020 ( 54.7%)  PrintModulePass
   0.0013 ( 37.6%)   0.0013 ( 37.6%)   0.0013 ( 37.6%)  VerifierPass
   0.0001 (  3.4%)   0.0001 (  3.4%)   0.0001 (  3.4%)  AnnotationRemarksPass
   0.0001 (  3.1%)   0.0001 (  3.1%)   0.0001 (  3.1%)  AlwaysInlinerPass
   0.0000 (  1.3%)   0.0000 (  1.3%)   0.0000 (  1.3%)  CoroConditionalWrapper
   0.0036 (100.0%)   0.0036 (100.0%)   0.0036 (100.0%)  Total

===-------------------------------------------------------------------------===
                    	Analysis execution timing report
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0014 seconds (0.0014 wall clock)

   ---User Time---   --User+System--   ---Wall Time---  --- Name ---
   0.0013 ( 94.8%)   0.0013 ( 94.8%)   0.0013 ( 94.8%)  VerifierAnalysis
   0.0000 (  3.1%)   0.0000 (  3.1%)   0.0000 (  3.1%)  TargetLibraryAnalysis
   0.0000 (  1.4%)   0.0000 (  1.4%)   0.0000 (  1.3%)  ProfileSummaryAnalysis
   0.0000 (  0.7%)   0.0000 (  0.7%)   0.0000 (  0.7%)  InnerAnalysisManagerProxy<llvm::AnalysisManager<llvm::Function>, llvm::Module>
   0.0014 (100.0%)   0.0014 (100.0%)   0.0014 (100.0%)  Total

===-------------------------------------------------------------------------===
                     	Miscellaneous Ungrouped Timers
===-------------------------------------------------------------------------===

   ---User Time---   --System Time--   --User+System--   ---Wall Time---  --- Name ---
   0.1974 ( 97.4%)   0.0001 (100.0%)   0.1975 ( 97.4%)   0.1981 ( 97.4%)  LLVM IR Generation Time
   0.0052 (  2.6%)   0.0000 (  0.0%)   0.0052 (  2.6%)   0.0052 (  2.6%)  Code Generation Time
   0.2026 (100.0%)   0.0001 (100.0%)   0.2027 (100.0%)   0.2033 (100.0%)  Total

===-------------------------------------------------------------------------===
                      	Clang front-end time report
===-------------------------------------------------------------------------===
  Total Execution Time: 6.5026 seconds (6.5048 wall clock)

   ---User Time---   --System Time--   --User+System--   ---Wall Time---  --- Name ---
   6.4867 (100.0%)   0.0159 (100.0%)   6.5026 (100.0%)   6.5048 (100.0%)  Clang front-end timer
   6.4867 (100.0%)   0.0159 (100.0%)   6.5026 (100.0%)   6.5048 (100.0%)  Total
```


**Example 2 (“whole compilation”):**


```bash
$ sudo ~/lldb/LLDB/bin/clang++ -ftime-report test.cpp
```


**Output:**


```bash
===-------------------------------------------------------------------------===
                      	Pass execution timing report
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0017 seconds (0.0017 wall clock)

   ---User Time---   --User+System--   ---Wall Time---  --- Name ---
   0.0014 ( 83.3%)   0.0014 ( 83.3%)   0.0014 ( 83.4%)  VerifierPass
   0.0001 (  7.4%)   0.0001 (  7.4%)   0.0001 (  7.3%)  AnnotationRemarksPass
   0.0001 (  6.6%)   0.0001 (  6.6%)   0.0001 (  6.6%)  AlwaysInlinerPass
   0.0000 (  2.7%)   0.0000 (  2.7%)   0.0000 (  2.7%)  CoroConditionalWrapper
   0.0017 (100.0%)   0.0017 (100.0%)   0.0017 (100.0%)  Total

===-------------------------------------------------------------------------===
                    	Analysis execution timing report
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0015 seconds (0.0015 wall clock)

   ---User Time---   --User+System--   ---Wall Time---  --- Name ---
   0.0014 ( 95.0%)   0.0014 ( 95.0%)   0.0014 ( 95.0%)  VerifierAnalysis
   0.0000 (  3.0%)   0.0000 (  3.0%)   0.0000 (  3.0%)  TargetLibraryAnalysis
   0.0000 (  1.3%)   0.0000 (  1.3%)   0.0000 (  1.3%)  ProfileSummaryAnalysis
   0.0000 (  0.7%)   0.0000 (  0.7%)   0.0000 (  0.7%)  InnerAnalysisManagerProxy<llvm::AnalysisManager<llvm::Function>, llvm::Module>
   0.0015 (100.0%)   0.0015 (100.0%)   0.0015 (100.0%)  Total

===-------------------------------------------------------------------------===
                     	Miscellaneous Ungrouped Timers
===-------------------------------------------------------------------------===

   ---User Time---   --System Time--   --User+System--   ---Wall Time---  --- Name ---
   0.1950 ( 85.3%)   0.0001 (100.0%)   0.1950 ( 85.3%)   0.1955 ( 85.4%)  LLVM IR Generation Time
   0.0335 ( 14.7%)   0.0000 (  0.0%)   0.0335 ( 14.7%)   0.0335 ( 14.6%)  Code Generation Time
   0.2285 (100.0%)   0.0001 (100.0%)   0.2286 (100.0%)   0.2291 (100.0%)  Total

===-------------------------------------------------------------------------===
                      	Pass execution timing report
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0188 seconds (0.0188 wall clock)

   ---User Time---   --User+System--   ---Wall Time---  --- Name ---
   0.0052 ( 27.8%)   0.0052 ( 27.8%)   0.0052 ( 27.8%)  X86 DAG->DAG Instruction Selection
   0.0032 ( 16.9%)   0.0032 ( 16.9%)   0.0032 ( 16.9%)  X86 Assembly Printer
   0.0027 ( 14.3%)   0.0027 ( 14.3%)   0.0027 ( 14.3%)  Pre-ISel Intrinsic Lowering
   0.0015 (  7.9%)   0.0015 (  7.9%)   0.0015 (  7.8%)  Fast Register Allocator
   0.0009 (  4.9%)   0.0009 (  4.9%)   0.0009 (  4.9%)  Module Verifier
   0.0008 (  4.4%)   0.0008 (  4.4%)   0.0008 (  4.4%)  Module Verifier #2
   0.0008 (  4.1%)   0.0008 (  4.1%)   0.0008 (  4.1%)  Prologue/Epilogue Insertion & Frame Finalization
   0.0005 (  2.4%)   0.0005 (  2.4%)   0.0005 (  2.4%)  Two-Address instruction pass
   0.0003 (  1.6%)   0.0003 (  1.6%)   0.0003 (  1.6%)  Finalize ISel and expand pseudo-instructions
   0.0002 (  1.2%)   0.0002 (  1.2%)   0.0002 (  1.2%)  Lower AMX type for load/store
   0.0002 (  1.1%)   0.0002 (  1.1%)   0.0002 (  1.1%)  MachineDominator Tree Construction
   0.0002 (  1.0%)   0.0002 (  1.0%)   0.0002 (  1.0%)  Machine Module Information
   0.0002 (  0.9%)   0.0002 (  0.9%)   0.0002 (  0.9%)  Lower constant intrinsics
   0.0001 (  0.8%)   0.0001 (  0.8%)   0.0002 (  0.9%)  X86 EFLAGS copy lowering
   0.0001 (  0.7%)   0.0001 (  0.7%)   0.0001 (  0.7%)  Free MachineFunction
   0.0001 (  0.6%)   0.0001 (  0.6%)   0.0001 (  0.6%)  Expand vector predication intrinsics
   0.0001 (  0.5%)   0.0001 (  0.5%)   0.0001 (  0.5%)  Check CFA info and insert CFI instructions if needed
   0.0001 (  0.5%)   0.0001 (  0.5%)   0.0001 (  0.5%)  Eliminate PHI nodes for register allocation
   0.0001 (  0.5%)   0.0001 (  0.5%)   0.0001 (  0.5%)  Post-RA pseudo instruction expansion pass
   0.0001 (  0.5%)   0.0001 (  0.5%)   0.0001 (  0.5%)  Scalarize Masked Memory Intrinsics
   0.0001 (  0.4%)   0.0001 (  0.4%)   0.0001 (  0.4%)  Expand reduction intrinsics
   0.0001 (  0.4%)   0.0001 (  0.4%)   0.0001 (  0.4%)  Remove unreachable blocks from the CFG
   0.0001 (  0.4%)   0.0001 (  0.4%)   0.0001 (  0.4%)  Exception handling preparation
   0.0001 (  0.4%)   0.0001 (  0.4%)   0.0001 (  0.4%)  Expand large div/rem
   0.0001 (  0.3%)   0.0001 (  0.3%)   0.0001 (  0.3%)  Insert stack protectors
   0.0001 (  0.3%)   0.0001 (  0.3%)   0.0001 (  0.3%)  Fast Tile Register Configure
   0.0001 (  0.3%)   0.0001 (  0.3%)   0.0001 (  0.3%)  Assignment Tracking Analysis
   0.0001 (  0.3%)   0.0001 (  0.3%)   0.0001 (  0.3%)  Expand Atomic instructions
   0.0000 (  0.3%)   0.0000 (  0.3%)   0.0000 (  0.3%)  Insert KCFI indirect call checks
   0.0000 (  0.2%)   0.0000 (  0.2%)   0.0000 (  0.2%)  X86 pseudo instruction expansion pass
   0.0000 (  0.2%)   0.0000 (  0.2%)   0.0000 (  0.2%)  Unpack machine instruction bundles
   0.0000 (  0.2%)   0.0000 (  0.2%)   0.0000 (  0.2%)  Expand large fp convert
   0.0000 (  0.2%)   0.0000 (  0.2%)   0.0000 (  0.2%)  X86 Lower Tile Copy
   0.0000 (  0.2%)   0.0000 (  0.2%)   0.0000 (  0.2%)  Argument Stack Rebase
   0.0000 (  0.2%)   0.0000 (  0.2%)   0.0000 (  0.2%)  Bundle Machine CFG Edges
   0.0000 (  0.2%)   0.0000 (  0.2%)   0.0000 (  0.2%)  X86 Indirect Branch Tracking
   0.0000 (  0.2%)   0.0000 (  0.2%)   0.0000 (  0.2%)  Fast Tile Register Preconfigure
   0.0000 (  0.2%)   0.0000 (  0.2%)   0.0000 (  0.2%)  Expand indirectbr instructions
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Insert fentry calls
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Stack Frame Layout Analysis
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Machine Optimization Remark Emitter
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Insert XRay ops
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Compressing EVEX instrs to VEX encoding when possible
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Live DEBUG_VALUE analysis
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  X86 PIC Global Base Reg Initialization
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Assumption Cache Tracker
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  X86 Indirect Thunks
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Contiguously Lay Out Funclets
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Implement the 'patchable-function' attribute
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  X86 FP Stackifier
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Machine Optimization Remark Emitter #2
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Prepare callbr
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Lazy Machine Block Frequency Analysis
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Machine Optimization Remark Emitter #3
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  StackMap Liveness Analysis
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Remove Redundant DEBUG_VALUE analysis
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  X86 DynAlloca Expander
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Fixup Statepoint Caller Saved
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.1%)  Local Stack Slot Allocation
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  X86 Load Value Injection (LVI) Ret-Hardening
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  X86 Insert Cache Prefetches
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.1%)  X86 Speculative Execution Side Effect Suppression
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  X86 speculative load hardening
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.1%)  X86 insert wait instruction
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Lazy Machine Block Frequency Analysis #3
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.1%)  X86 Return Thunks
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.1%)  Machine Sanitizer Binary Metadata
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  Analyze Machine Code For Garbage Collection
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  Pseudo Probe Inserter
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  X86 vzeroupper inserter
   0.0000 (  0.1%)   0.0000 (  0.1%)   0.0000 (  0.0%)  Lazy Machine Block Frequency Analysis #2
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  X86 Discriminate Memory Operands
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  Lower AMX intrinsics
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  Safe Stack instrumentation pass
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  Lower Garbage Collection Instructions
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  Shadow Stack GC Lowering
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  Create Garbage Collector Module Metadata
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  Target Pass Configuration
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  Profile summary info
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  Machine Branch Probability Analysis
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  Target Transform Information
   0.0000 (  0.0%)   0.0000 (  0.0%)   0.0000 (  0.0%)  Target Library Information
   0.0188 (100.0%)   0.0188 (100.0%)   0.0188 (100.0%)  Total

===-------------------------------------------------------------------------===
                             	DWARF Emission
===-------------------------------------------------------------------------===
  Total Execution Time: 0.0003 seconds (0.0004 wall clock)

   ---User Time---   --User+System--   ---Wall Time---  --- Name ---
   0.0003 (100.0%)   0.0003 (100.0%)   0.0004 (100.0%)  DWARF Exception Writer
   0.0003 (100.0%)   0.0003 (100.0%)   0.0004 (100.0%)  Total

===-------------------------------------------------------------------------===
                      	Clang front-end time report
===-------------------------------------------------------------------------===
  Total Execution Time: 6.4509 seconds (6.4515 wall clock)

   ---User Time---   --System Time--   --User+System--   ---Wall Time---  --- Name ---
   6.4310 (100.0%)   0.0199 (100.0%)   6.4509 (100.0%)   6.4515 (100.0%)  Clang front-end timer
   6.4310 (100.0%)   0.0199 (100.0%)   6.4509 (100.0%)   6.4515 (100.0%)  Total
```


According to the author of [this post](https://aras-p.info/blog/2019/01/12/Investigating-compile-times-and-Clang-ftime-report/), this tool is not very useful, nor were other tools for investigating compile times, unless you are one of the developers of the compiler. Hence, the author proposed the `-ftime-trace` option.


### -ftime-trace

This option generates a JSON file that can be visualized in Chrome (using `chrome://tracing`) in a flame chart style, where the horizontal axis represents the time and the vertical axis represents the nested “callstacks”.

**Example:**


```bash
$ sudo ~/lldb/LLDB/bin/clang++ -ftime-trace test.cpp
```


**Output** (for a better view, use `chrome://tracing` and open [this file](./a-test.json)):
![image](https://github.com/junior-jl/profiling-clang/assets/69206952/8f411a63-d230-4784-92f1-187b5cd23051)

- If you select a block and press <kbd>m</kbd>, the block is marked, showing the execution time for it. For example, the biggest "Source" block shows 6.171 seconds as the execution time for it.

![image](https://github.com/junior-jl/profiling-clang/assets/69206952/b72a5e3b-4f44-4281-be94-ec4414700e0d)

- In the bottom left corner, you can check details of what is that "Source". Here, we have the information that `iostream` include is taking a lot of time.

![image](https://github.com/junior-jl/profiling-clang/assets/69206952/07e99a1a-09ea-4cd7-9379-87ada96dbc44)

- If you click the magnifying glass icon next to 'Title', it will search for occurrences of that title. That is quite useless when you click on something like 'Source', but it can be useful if you click on 'ExecuteCompiler', for example, because you can check where that process is called.

![image](https://github.com/junior-jl/profiling-clang/assets/69206952/f85cecc6-eb4a-405b-bcc7-5e522957277c)

- You can also use <kbd>/</kbd> to search some keyword like `manipulateArray`. You'll notice that there are 6 occurrences (2 for CodeGen Function, 2 for `ParseFunctionDefinition` and 2 for OptFunction with their mangled names for `int` and `double`). Again, as an example, we can see in which files Clang calls `ParseFunctionDefinition` and investigate.

![image](https://github.com/junior-jl/profiling-clang/assets/69206952/fbd85c61-c12a-44a7-a7db-cfb49fbb22f3)
