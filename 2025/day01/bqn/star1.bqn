# Imports
str ⇐ •path ∾ "/strings.bqn"

# Input
input ← •file.Lines •wdpath ∾ "/" ∾ ·⊑ •args

# Constants
initState ← 50
numStates ← 100

# Functions
ExtractValues ← •ParseFloat¨ 1⊸↓¨
ExtractSigns ← ¯1 ⋆ 'L'= ⊑¨
CalculatePositions ← +` initState ∾ (ExtractValues × ExtractSigns)
CalculatePassword ← +´ 0 = numStates | CalculatePositions

# Solution
password ← CalculatePassword input
•Show "The password is: " ∾ •Fmt password