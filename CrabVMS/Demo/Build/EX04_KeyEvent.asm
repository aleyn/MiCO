;Generate by CrabScript v3.0
;Compile Mode: 3
;OnKey1 :
{$D 332, 340}
{$E $01000021}
::OnKey1::
{$N 'OnKey1', 'L', 0}
  FUNC <OnKey1>
  PUSH #L, #F, #Q, #V, #M
  VAR  #L, 0
{$A True}
;board.LED2 = LED_RED;
{$D 360, 381}
  GET  #Q, 2 ;LED_RED
  TYPE #W, (U:01)
  PORT #D, $0002 ;Board.LED2
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;Delay(500)
{$D 385, 395}
  VAR  #F, 5
  GET  #V, 500
  BASE #M, #F
  SEEK #M, $0001 ;MSec
  TYPE #W, (U:04)
  SAVE #M, #W, #V ;Delay[1]:MSec
  TYPE #W, (V:01)
  CAPI [&000004] ;Delay
  FREE #F
;board.LED2 = LED_OFF;
{$D 462, 483}
  GET  #Q, 0 ;LED_OFF
  TYPE #W, (U:01)
  PORT #D, $0002 ;Board.LED2
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
{$D 485, 486}
::OnKey1.@::
{$A False}
  FREE #L
  POP  #L, #F, #Q, #V, #M
  IRET
;main
{$D 490, 494}
::main::
{$N 'main', 'P', 0}
{$N 'main', 'L', 0}
  FUNC <main>
  VAR  #P, 0
  VAR  #L, 0
{$A True}
;PrintLn('=== Key Event Demo ===')
{$D 517, 550}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.1> ;'=== Key Event Demo ==='
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
;OpenEvent()
{$D 579, 590}
  INTR $8000
  FREE #F
;repeat
{$D 601, 607}
::main.4L::
;until error;
{$D 621, 633}
::main.4C::
  MOV  #Q, #E ;Global.Error
  TST  #Q
  JOF  <main.4L>
::main.4X::
;CloseEvent()
{$D 663, 675}
  INTR $0000
  FREE #F
{$D 680, 681}
::main.@::
{$A False}
  INTR $0000
  FREE #L
  FREE #P
  JMP  <@CRABSCRIPT.@>
