CPPBench
========

A benchmark for C++ language features


Created by Martin Jachimowicz, 2013/10

Licensed under the MIT License


Instructions:

run using number of iterations as argument, e.g.

./CPPBench 10000000000


Sample results:
>  TIMED 'inlineNothing' with 10000000000 iterations: 26060005 mus

>  TIMED 'nothingFunction' with 10000000000 iterations: 35957462 mus

>  TIMED 'inlineNothingFunctionCaller' with 10000000000 iterations: 47180103 mus

>  TIMED 'heavyNothingFunctionCaller' with 10000000000 iterations: 52189290 mus

>  TIMED 'heavierNothingFunctionCaller' with 10000000000 iterations: 65099542 mus

>  TIMED 'StaticClass::nothing' with 10000000000 iterations: 39084690 mus

>  TIMED 'functionPointerCaller' with 10000000000 iterations: 48936672 mus

>  TIMED 'templatedFunctionPointerCaller<&nothingFunction>' with 10000000000 iterations: 49580818 mus

>  TIMED 'nothingFunctorCaller' with 10000000000 iterations: 115464060 mus

>  TIMED 'nothingLambdaCaller' with 10000000000 iterations: 52232254 mus

>  TIMED 'nothingMethodCaller<NonVirtualClass>' with 10000000000 iterations: 61311713 mus

>  TIMED 'nothingPointerToMethodCaller<NonVirtualClass>' with 10000000000 iterations: 70488509 mus

>  TIMED '(nothingTemplatedPointerToMethodCaller<NonVirtualClass, &NonVirtualClass::nothing>)' with 10000000000 iterations: 72693410 mus

>  TIMED 'nothingMemberFunctorCaller<NonVirtualClass>' with 10000000000 iterations: 149129008 mus

>  TIMED 'nothingMethodCaller<BaseClass>' with 10000000000 iterations: 62122058 mus

>  TIMED 'nothingPointerToMethodCaller<BaseClass>' with 10000000000 iterations: 72561518 mus

>  TIMED '(nothingTemplatedPointerToMethodCaller<BaseClass, &BaseClass::nothing>)' with 10000000000 iterations: 69718002 mus

>  TIMED 'nothingMemberFunctorCaller<BaseClass>' with 10000000000 iterations: 171513009 mus

>  TIMED 'nothingMethodCaller<DerivedClass>' with 10000000000 iterations: 57567536 mus

>  TIMED 'nothingPointerToMethodCaller<DerivedClass>' with 10000000000 iterations: 74882275 mus

>  TIMED '(nothingTemplatedPointerToMethodCaller<DerivedClass, &DerivedClass::nothing>)' with 10000000000 iterations: 66338734 mus

>  TIMED 'nothingMemberFunctorCaller<DerivedClass>' with 10000000000 iterations: 170460079 mus




