
#include <cassert>
#include <functional>
#include "timer.hpp"



namespace call_bench {

	typedef void (*tFunctionPointer)();
	typedef std::function<void(void)> tFunctor;

	inline void inlineNothing() {
		volatile int i = 0;
		//		asm("");
	}
	

	__attribute__((noinline)) void nothingFunction() {
		inlineNothing();
	}
	inline void inlineNothingFunctionCaller() {
		nothingFunction();
	}
	
	__attribute__((noinline)) void heavyNothingFunctionCaller() {
		nothingFunction();
	}
	
	__attribute__((noinline)) void heavierNothingFunctionCaller() {
		heavyNothingFunctionCaller();
	}
	

	struct StaticClass {
		__attribute__((noinline)) static void nothing() {
			inlineNothing();
		}
	};


	struct NonVirtualClass {
		NonVirtualClass() {}
		__attribute__((noinline)) void nothing() const {
			inlineNothing();
		}
	};


	struct BaseClass {
		BaseClass() {}
		__attribute__((noinline)) virtual void nothing() const {
			inlineNothing();
		}
	};

	struct DerivedClass {
		DerivedClass() {}
		__attribute__((noinline)) virtual void nothing() const {
			inlineNothing();
		}
	};


	class FunctionPointerCaller {
	public:
		explicit FunctionPointerCaller(tFunctionPointer fp) 
		: fp_(fp) {
			assert(fp_);
		}
		inline void nothing() const {
			fp_();
		}
	private:
		tFunctionPointer fp_;
	};

	class FunctorCaller {
	public:
		explicit FunctorCaller(tFunctor functor) 
		: functor_(functor) {
			assert(functor_);
		}
		inline void nothing() const {
			functor_();
		}
	private:
		tFunctor functor_;
	};


	template<tFunctionPointer FP>
	struct TemplatedFunctionPointerCaller {
		inline void nothing() const {
			FP();
		}
	};

	template<typename T>
	class MethodCaller {
		typedef void (T::*tMethod)();
	public:
		explicit MethodCaller(const T& t, tMethod method)
		: t_(t)
		,	method_(method) {
			assert(method_);
		}
		inline void nothing() const {
			t_ .* method_();
		}
	private:	
		const T& t_;
		tMethod method_;
	};
	
	template<typename T, void (T::*METHOD)()>
	class TemplatedMethodCaller {
		typedef void (T::*tMethod)();
	public:
		explicit TemplatedMethodCaller(const T& t)
		: t_(t) {
		}
		inline void nothing() const {
			t_ .* METHOD();
		}
	private:	
		const T& t_;
	};

	
	
	inline void nothingLambdaCaller() {
		static const auto lambda_ = [](){ inlineNothing(); };
		lambda_();
	}

	inline void functionPointerCaller() {
		static const tFunctionPointer fp_ = &nothingFunction;
		fp_();
	}
	

	template<tFunctionPointer FP>
	inline void templatedFunctionPointerCaller() {
		static_assert(FP, "expected non-null function pointer");
		FP();
	}

	template<typename T>
	inline void nothingMethodCaller() {
		static const T obj_;
		obj_.nothing();
	}


	template<typename T>
	inline void nothingPointerToMethodCaller() {
		static const T obj_;
		typedef void (T::*tMethodPtr)() const;
		static const tMethodPtr method_ = &T::nothing;
		(obj_ .* method_)();
	}


	template<typename T, void (T::*METHOD)() const>
	inline void nothingTemplatedPointerToMethodCaller() {
		static_assert(METHOD, "expected non-null method pointer");
		static const T obj_;
		(obj_ .* METHOD)();
	}


	inline void nothingFunctorCaller() {
		static const tFunctor func_ { nothingFunction };
		func_();
	}


	template<typename T>
	inline void nothingMemberFunctorCaller() {
		static const T obj_;
		static const tFunctor functor_ = std::bind(&T::nothing, &obj_);
		functor_();
	}

	static const size_t NUM_ITERATIONS = 10000000000;

	
	
	void call_bench(const size_t numIterations) {
		
//		{
//			std::chrono::time_point<std::chrono::system_clock> start, end;
//			start = std::chrono::system_clock::now();
//			for (size_t i = 0; i < NUM_ITERATIONS; ++i) {
//				nothingFunction();
//			}
//			end = std::chrono::system_clock::now();
//			auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
//			std::cout << "TIMED 'nothingFunction_' with " << NUM_ITERATIONS << " iterations: " << elapsed << "ns" << std::endl;
//		}
		
		TIME( inlineNothing, numIterations );
		TIME( nothingFunction, numIterations );
		TIME( inlineNothingFunctionCaller, numIterations );
		TIME( heavyNothingFunctionCaller, numIterations );
		TIME( heavierNothingFunctionCaller, numIterations );
		TIME( StaticClass::nothing, numIterations );
		TIME( functionPointerCaller, numIterations );
		TIME( templatedFunctionPointerCaller<&nothingFunction>, numIterations );
		TIME( nothingFunctorCaller, numIterations );
		TIME( nothingLambdaCaller, numIterations );

		TIME( nothingMethodCaller<NonVirtualClass>, numIterations );
		TIME( nothingPointerToMethodCaller<NonVirtualClass>, numIterations );
		TIME( (nothingTemplatedPointerToMethodCaller<NonVirtualClass, &NonVirtualClass::nothing>), numIterations );
		TIME( nothingMemberFunctorCaller<NonVirtualClass>, numIterations );
	
		TIME( nothingMethodCaller<BaseClass>, numIterations );
		TIME( nothingPointerToMethodCaller<BaseClass>, numIterations );
		TIME( (nothingTemplatedPointerToMethodCaller<BaseClass, &BaseClass::nothing>), numIterations );
		TIME( nothingMemberFunctorCaller<BaseClass>, numIterations );

		TIME( nothingMethodCaller<DerivedClass>, numIterations );
		TIME( nothingPointerToMethodCaller<DerivedClass>, numIterations );
		TIME( (nothingTemplatedPointerToMethodCaller<DerivedClass, &DerivedClass::nothing>), numIterations );
		TIME( nothingMemberFunctorCaller<DerivedClass>, numIterations );
	}
	
	
}
















