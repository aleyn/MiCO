;Generate by CrabScript v3.0
;Compile Mode: 3
;main
{$D 142, 146}
::main::
{$N 'main', 'P', 0}
{$N 'main', 'L', 0}
  FUNC <main>
  VAR  #P, 0
  VAR  #L, 0
{$A True}
;PrintLn('LED Flash Demo')
{$D 169, 194}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.1> ;'LED Flash Demo'
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
;repeat
{$D 201, 207}
::main.3L::
;Board.LED1 = LED_BLUE;
{$D 218, 240}
  GET  #Q, 1 ;LED_BLUE
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.LED1
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;Delay(500)
{$D 270, 280}
  VAR  #F, 5
  GET  #V, 500
  BASE #M, #F
  SEEK #M, $0001 ;MSec
  TYPE #W, (U:04)
  SAVE #M, #W, #V ;Delay[1]:MSec
  TYPE #W, (V:01)
  CAPI [&000004] ;Delay
  FREE #F
;Board.LED1 = LED_OFF;
{$D 314, 335}
  GET  #Q, 0 ;LED_OFF
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.LED1
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;Delay(500)
{$D 356, 366}
  VAR  #F, 5
  GET  #V, 500
  BASE #M, #F
  SEEK #M, $0001 ;MSec
  TYPE #W, (U:04)
  SAVE #M, #W, #V ;Delay[1]:MSec
  TYPE #W, (V:01)
  CAPI [&000004] ;Delay
  FREE #F
;Board.LED1 = LED_RED;
{$D 400, 421}
  GET  #Q, 2 ;LED_RED
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.LED1
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;Delay(500)
{$D 452, 462}
  VAR  #F, 5
  GET  #V, 500
  BASE #M, #F
  SEEK #M, $0001 ;MSec
  TYPE #W, (U:04)
  SAVE #M, #W, #V ;Delay[1]:MSec
  TYPE #W, (V:01)
  CAPI [&000004] ;Delay
  FREE #F
;Board.LED1 = LED_OFF;
{$D 496, 517}
  GET  #Q, 0 ;LED_OFF
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.LED1
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;Delay(500)
{$D 538, 548}
  VAR  #F, 5
  GET  #V, 500
  BASE #M, #F
  SEEK #M, $0001 ;MSec
  TYPE #W, (U:04)
  SAVE #M, #W, #V ;Delay[1]:MSec
  TYPE #W, (V:01)
  CAPI [&000004] ;Delay
  FREE #F
;until error;
{$D 582, 594}
::main.3C::
  MOV  #Q, #E ;Global.Error
  TST  #Q
  JOF  <main.3L>
::main.3X::
{$D 596, 597}
::main.@::
{$A False}
  INTR $0000
  FREE #L
  FREE #P
  JMP  <@CRABSCRIPT.@>
