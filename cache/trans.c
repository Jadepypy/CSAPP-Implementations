/* * trans.c - Matrix Transpose
 * The 64x64 matrix is a nightmare because of conflict misses. 
 * Using 4x4 or 8x8 blocks. 
 */

void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
    int i, j, k, l;
    int v1, v2, v3, v4, v5, v6, v7, v8; // Local variables to use registers

    if (N == 32) {
        for (i = 0; i < N; i += 8) {
            for (j = 0; j < M; j += 8) {
                for (k = i; k < i + 8; k++) {
                    // Pulling all 8 at once to avoid thrashing the cache line
                    v1 = A[k][j]; v2 = A[k][j+1]; v3 = A[k][j+2]; v4 = A[k][j+3];
                    v5 = A[k][j+4]; v6 = A[k][j+5]; v7 = A[k][j+6]; v8 = A[k][j+7];
                    
                    B[j][k] = v1; B[j+1][k] = v2; B[j+2][k] = v3; B[j+3][k] = v4;
                    B[j+4][k] = v5; B[j+5][k] = v6; B[j+6][k] = v7; B[j+7][k] = v8;
                }
            }
        }
    }
    // TODO: Add 61x67 case (it's weirdly easier because it doesn't align perfectly)
}