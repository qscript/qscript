/*
 * =====================================================================================
 *
 *       Filename:  optimized-scalar-product-4-stages.cpp
 *
 *    Description:  
 *
 *       http://www.drdobbs.com/optimizing-cc-with-inline-assembly-progr/184401967?pgno=1
 *        Version:  1.0
 *        Created:  Monday 08 October 2012 02:05:28  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

float ScalarProduct( float* a1, float* a2, int n )
{
  float ans = 0.0;
  register int i;

  for( i = 0; i < n; ++i )
    ans += a1[i] * a2[i];
  return( ans );
}


float ScalarProduct2( float* a1, float* a2, int n )
{
  float ans = 0.0;
  register int i;

  if( n >= 8 )
  {
    for( i = 0; i < ( n >> 3 ); ++i, a1 += 8, a2 += 8 )
      ans += a1[0] * a2[0] + a1[1] * a2[1] +
             a1[2] * a2[2] + a1[3] * a2[3] +
             a1[4] * a2[4] + a1[5] * a2[5] +
             a1[6] * a2[6] + a1[7] * a2[7];
    n -= i << 3;
  }
  for( i = 0; i < n; ++i )
    ans += a1[i] * a2[i];
  return( ans );
}

float ScalarProduct3( float* a1, float* a2, int n )
{
  float ans[4] __attribute__ ((aligned(16)));
  register int i;
  if( n >= 8 )
  {
    __asm__ __volatile__(
        "xorps      %%xmm0, %%xmm0"
        : /* outputs */
        : /* inputs */
        : /* clobbered */ "xmm0" );
    for( i = 0; i < ( n >> 3 ); ++i )
    {
      __asm__ __volatile__(
            "movups     (%0), %%xmm1\n\t"
            "movups     16(%0), %%xmm2\n\t"
            "movups     (%1), %%xmm3\n\t"
            "movups     16(%1), %%xmm4\n\t"
            "add        $32,%0\n\t"
            "add        $32,%1\n\t"
            "mulps      %%xmm3, %%xmm1\n\t"
            "mulps      %%xmm4, %%xmm2\n\t"
            "addps      %%xmm2, %%xmm1\n\t"
            "addps      %%xmm1, %%xmm0"
            : /* outputs */ "+r" ( a1 ), "+r" ( a2 )
            : /* inputs */
            : /* clobbered */ "xmm0", "xmm1", "xmm2", "xmm3", "xmm4" );
    }
    __asm__ __volatile__(
        "movaps     %%xmm0, %0"
        : /* outputs */ "=m" ( ans )
        : /* inputs */
        : /* clobbered */ "xmm0", "memory" );
    n -= i << 3;
    ans[0] += ans[1] + ans[2] + ans[3];
  }
  else
    ans[0] = 0.0;
  for( i = 0; i < n; ++i )
    ans[0] += a1[i] * a2[i];
  return( ans[0] );
}

// This class doesnt compile - but get the gist of it
// its important
#if 0
template <class T>
class AlignedArray 
{
public:
  AlignedArray( unsigned int numElements )
    : _mNumElements( ( int )numElements )
  {
    _mData = AllocMem( numElements );
  }
  AlignedArray( const AlignedArray<T>& array )
    : _mNumElements( array.NumElements() )
  {
    _mData = AllocMem( NumElements() );
    *this = array;
  }
  virtual ~AlignedArray() { if( _mData ) delete _mData; }
  int NumElements() const { return( _mNumElements ); }
  AlignedArray<T>& operator=( const AlignedArray<T>& array )
  {
    int n = this->NumElements() <? array.NumElements();
    for( int i = 0; i < n; ++i )
      ( *this )[i] = array[i];
    return( *this );
  }
  T operator[]( int idx ) const
  {
    assert( ( idx >= 0 ) && ( idx < _mNumElements ) ); 
    return( _mData[idx] );
  }
  T& operator[]( int idx )
  {
    assert( ( idx >= 0 ) && ( idx < _mNumElements ) ); 
    return( _mData[idx] );
  }
  T ScalarProduct( const AlignedArray<T>& array )
  {
    int n = this->NumElements() <? array.NumElements();
    T ans = 0.0;
    for( int i = 0; i < n; ++i )
      ans += ( *this )[i] * array[i];
    
    return( ans );
  }
  // ...other operators/functions not shown
protected:
  operator T*() const { return( _mData ); }
private:
  T* AllocMem( int numElements )
  {
    char *ptr = new char[numElements * sizeof( T ) + 16];
    int offset = ( int )ptr & 0xf;
    if( offset )
      ptr = ( char* )( ( unsigned int )ptr + 16 - offset );
    return( ( T* )ptr );
  }
  int _mNumElements;
  T* _mData;
};
// SSE 'packed single' implementation
template <> float
AlignedArray<float>::ScalarProduct( const AlignedArray<float>& array )
{
  float *data1 = *this, *data2 = array;
  float ans[4] __attribute__ ((aligned(16)));
  int n = this->NumElements() <? array.NumElements();
  register int i;

  if( n >= 8 )
  {
    __asm__ __volatile__(
        "xorps      %%xmm0, %%xmm0"
        : /* outputs */
        : /* inputs */
        : /* clobbered */ "xmm0" );

    for( i = 0; i < ( n >> 3 ); ++i )
    {
      __asm__ __volatile__(
            "movaps     (%0), %%xmm1\n\t"
            "movaps     16(%0), %%xmm2\n\t"
            "mulps      (%1), %%xmm1\n\t"
            "mulps      16(%1), %%xmm2\n\t"
            "add        $32,%0\n\t"
            "add        $32,%1\n\t"
            "addps      %%xmm2, %%xmm1\n\t"
            "addps      %%xmm1, %%xmm0"
            : /* outputs */ "+r" ( data1 ), "+r" ( data2 )
            : /* inputs */
            : /* clobbered */ "xmm0", "xmm1", "xmm2" );
    }
    __asm__ __volatile__(
        "movaps     %%xmm0, %0"
        : /* outputs */ "=m" ( ans )
        : /* inputs */
        : /* clobbered */ "xmm0", "memory" );
    n -= i << 3;
    ans[0] += ans[1] + ans[2] + ans[3];
  }
  else
    ans[0] = 0.0;
  for( i = 0; i < n; ++i )
    ans[0] += data1[i] * data2[i];
  return( ans[0] );
}
// SSE2 'packed double' implementation
template <> double
AlignedArray<double>::ScalarProduct( const AlignedArray<double>& array )
{
  double *data1 = *this, *data2 = array;
  double ans[2] __attribute__ ((aligned(16)));
  int n = this->NumElements() <? array.NumElements();
  register int i;
  
  if( n >= 4 )
  {
    __asm__ __volatile__(
        "xorpd      %%xmm0, %%xmm0"
        : /* outputs */
        : /* inputs */

        : /* clobbered */ "xmm0" );

    for( i = 0; i < ( n >> 2 ); ++i )
    {
      __asm__ __volatile__(
            "movapd     (%0), %%xmm1\n\t"
            "movapd     16(%0), %%xmm2\n\t"
            "mulpd      (%1), %%xmm1\n\t"
            "mulpd      16(%1), %%xmm2\n\t"
            "add        $32,%0\n\t"
            "add        $32,%1\n\t"
            "addpd      %%xmm2, %%xmm1\n\t"
            "addpd      %%xmm1, %%xmm0"
            : /* outputs */ "+r" ( data1 ), "+r" ( data2 )
            : /* inputs */
            : /* clobbered */ "xmm0", "xmm1", "xmm2" );
    }
    __asm__ __volatile__(
        "movapd     %%xmm0, %0"
        : /* outputs */ "=m" ( ans )
        : /* inputs */
        : /* clobbered */ "xmm0", "memory" );
    
    n -= i << 2;
    ans[0] += ans[1];
  }
  else
    ans[0] = 0.0;
  for( i = 0; i < n; ++i )
    ans[0] += data1[i] * data2[i];
  
  return( ans[0] );
}
#endif /* 0 */
