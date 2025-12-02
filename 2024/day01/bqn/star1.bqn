str ⇐ •Import "strings.bqn"

Parse ← >· •ParseFloat¨¨ ·((0≠≠¨) ⊸/)¨ ' 'str.Split¨ •file.Lines
input ← Parse ⊑ •args

CalculateDistance ← +´·|∘-˝·∧˘⍉

•Show "The total distance between the lists is: " ∾ •Fmt CalculateDistance input