# Input
input ← •file.Lines •wdpath ∾ "/" ∾ ·⊑ •args

# Functions
CalculateAnswer ← 0˙

# Solution
answer ← CalculateAnswer input
•Show "Answer is: " ∾ •Fmt answer