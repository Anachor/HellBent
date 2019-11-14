
/// iterating over all subsets : O(3^n)
for (int mask = 0; mask < (1<<n); mask++){
	F[mask] = A[0];
    /// iterate over all the subsets of the mask
    for(int i = mask; i > 0; i = (i-1) & mask){
    	F[mask] += A[i];
    }
}
