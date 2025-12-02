str ⇐ •Import "strings.bqn"

Parse ← >· •ParseFloat¨¨ ·((0≠≠¨) ⊸/)¨ ' 'str.Split¨ •file.Lines
input ← Parse ⊑ •args
c0 ← 0⊏⍉input
c1 ← 1⊏⍉input
table ← c0=⌜c1

•Show 

distance ← +´c0×·+˝⍉table

•Show "The total distance between the lists is: " ∾ •Fmt distance