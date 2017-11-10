// Serial
void SerialApplyFoo( float b[], const float a[], size_t n ){
   for( size_t i=0; i<n; ++i )
      b[i] = Foo(a[i]);
}

// Intel TBB
void ParallelApplyFoo (float b[], const float a[], size_t n){
   tbb::parallel_for(
     tbb::blocked_range<size_t>(0,n),
       [=](tbb::blocked_range<size_t> r) {
        for (size_t i=r.begin(); i!=r.end(); ++i)
         b[i] = Foo(a[i]);
    });
}
