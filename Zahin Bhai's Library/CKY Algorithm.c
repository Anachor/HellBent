The Cocke–Younger–Kasami algorithm (alternatively called CYK, or CKY) is a parsing algorithm for context-free grammars,
named after its inventors, John Cocke, Daniel Younger and Tadao Kasami. It employs bottom-up parsing and dynamic programming.

The standard version of CYK operates only on context-free grammars given in Chomsky normal form (CNF).
However any context-free grammar may be transformed to a CNF grammar expressing the same language.

The importance of the CYK algorithm stems from its high efficiency in certain situations. Using Landau symbols,
the worst case running time of CYK is O(N^3 * |G|), where N is the length of the parsed string and |G| is the
size of the CNF grammar G. This makes it one of the most efficient parsing algorithms in terms of worst-case
asymptotic complexity, although other algorithms exist with better average running time in many practical scenarios.

Pseudocode:

let the input be a string S consisting of n characters: a1 ... an.
let the grammar contain r nonterminal symbols R1 ... Rr.
This grammar contains the subset Rs which is the set of start symbols.
let P[n,n,r] be an array of booleans. Initialize all elements of P to false.
for each i = 1 to n
  for each unit production Rj -> ai
    set P[1,i,j] = true
for each i = 2 to n -- Length of span
  for each j = 1 to n-i+1 -- Start of span
    for each k = 1 to i-1 -- Partition of span
      for each production RA -> RB RC
        if P[k,j,B] and P[i-k,j+k,C] then set P[i,j,A] = true
if any of P[n,1,x] is true (x is iterated over the set s, where s are all the indices for Rs) then
  S is member of language
else
  S is not member of language
