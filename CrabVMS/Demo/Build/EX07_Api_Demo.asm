;Generate by CrabScript v3.0
;Compile Mode: 3
;main
{$D 333, 337}
::main::
{$N 'main', 'P', 0}
{$N 'main', 'L', 1}
{$V 'Value1', $000000, 'N', 4, 0}
  FUNC <main>
  VAR  #P, 0
  VAR  #L, 4
{$A True}
;PrintLn('=== Custom API Demo ===')
{$D 360, 394}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.1> ;'=== Custom API Demo ==='
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
;int Value1;
{$D 401, 412}
;Board.LED1 = LED_RED;
{$D 418, 439}
  GET  #Q, 2 ;LED_RED
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.LED1
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;Value1 = MyAPIFunc(1,2);
{$D 482, 506}
  VAR  #F, 12
  GET  #V, 1
  BASE #M, #F
  SEEK #M, $0004 ;Param1
  TYPE #W, (N:04)
  SAVE #M, #W, #V ;MyAPIFunc[1]:Param1
  GET  #V, 2
  BASE #M, #F
  SEEK #M, $0008 ;Param2
  TYPE #W, (N:04)
  SAVE #M, #W, #V ;MyAPIFunc[2]:Param2
  TYPE #W, (N:04)
  CAPI [&000046] ;MyAPIFunc
  BASE #M, #F
  SEEK #M, $0000 ;Result
  TYPE #W, (N:04)
  LOAD #Q, #W, #M
  FREE #F
  BASE #M, #L
  SEEK #M, $0000 ;Value1
  TYPE #W, (N:04)
  SAVE #M, #W, #Q
;PrintLn("Result = " # Value1)
{$D 528, 557}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.2> ;"Result = "
  READ #V, #W, #D
  BASE #M, #L
  SEEK #M, $0000 ;Value1
  TYPE #W, (N:04)
  LOAD #X, #W, #M
  STRA #V, #X
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::main.4.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
;Board.LED1 = LED_OFF;
{$D 564, 585}
  GET  #Q, 0 ;LED_OFF
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.LED1
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
{$D 587, 588}
::main.@::
{$A False}
  INTR $0000
  FREE #L
  FREE #P
  JMP  <@CRABSCRIPT.@>
