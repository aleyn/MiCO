;Generate by CrabScript v3.0
;Compile Mode: 3
;main
{$D 134, 138}
::main::
{$N 'main', 'P', 0}
{$N 'main', 'L', 0}
  FUNC <main>
  VAR  #P, 0
  VAR  #L, 0
{$A True}
;PrintLn('LED Control Demo')
{$D 161, 188}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.1> ;'LED Control Demo'
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::main.1.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
;Board.LED1 = LED_BLUE;
{$D 221, 243}
  GET  #Q, 1 ;LED_BLUE
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.LED1
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;Board.LED2 = LED_RED;
{$D 275, 296}
  GET  #Q, 2 ;LED_RED
  TYPE #W, (U:01)
  PORT #D, $0002 ;Board.LED2
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
{$D 301, 302}
::main.@::
{$A False}
  INTR $0000
  FREE #L
  FREE #P
  JMP  <@CRABSCRIPT.@>
