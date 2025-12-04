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
Normalise ← CalculatePositions ÷ numStates˙
CountUp ← +´ 0 ⌈ (1⊸↓) - ¯1⊸↓
CalculatePassword ← +´ ·CountUp˘∘⌊ (⊢≍-)∘Normalise

# Solution
password ← CalculatePassword input
•Show "The password to open the door is: " ∾ •Fmt password