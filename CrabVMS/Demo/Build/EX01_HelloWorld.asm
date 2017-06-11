;Generate by CrabScript v3.0
;Compile Mode: 3
;main
{$D 277, 281}
::main::
{$N 'main', 'P', 0}
{$N 'main', 'L', 0}
  FUNC <main>
  VAR  #P, 0
  VAR  #L, 0
{$A True}
;Print('Hello World')
{$D 288, 308}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.1> ;'Hello World'
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;Print[1]:Text
  TYPE #W, (V:01)
  CAPI [&000003] ;Print
::main.1.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
{$D 311, 312}
::main.@::
{$A False}
  INTR $0000
  FREE #L
  FREE #P
  JMP  <@CRABSCRIPT.@>
