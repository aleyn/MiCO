;Generate by CrabScript v3.0
;Compile Mode: 3
;boolean RetyFlag;
{$D 222, 239}
;void Welcome()
{$D 259, 273}
::Welcome::
{$N 'Welcome', 'P', 0}
{$N 'Welcome', 'L', 0}
  FUNC <Welcome>
  INTR $2000
  PUSH #L, #P, #V, #M
  VAR  #L, 0
  MOV  #P, #F
  INTR $1000
{$A True}
;PrintLn('============ Crab for MiCO ===============')
{$D 280, 333}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.1> ;'============ Crab for MiCO ==============='
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::Welcome.1.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
;PrintLn('= Power by Crab SDK 2.0 / MiCO SDK 3.2.2 =')
{$D 338, 391}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.2> ;'= Power by Crab SDK 2.0 / MiCO SDK 3.2.2 ='
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::Welcome.3.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
;PrintLn('= Program by aleyn.wu   / MXCHIP         =')
{$D 396, 449}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.3> ;'= Program by aleyn.wu   / MXCHIP         ='
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::Welcome.5.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
;PrintLn('= Support EMW3166, EMW3239               =')
{$D 454, 507}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.4> ;'= Support EMW3166, EMW3239               ='
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::Welcome.7.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
;PrintLn('=                                        =')
{$D 512, 565}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.5> ;'=                                        ='
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::Welcome.9.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
;PrintLn('= Handware Control Demo                  =')
{$D 570, 623}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.6> ;'= Handware Control Demo                  ='
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::Welcome.11.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
;PrintLn('==========================================')
{$D 628, 681}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.7> ;'=========================================='
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::Welcome.13.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
{$D 684, 685}
::Welcome.@::
  INTR $2000
{$A False}
  MOV  #F, #P
  FREE #L
  POP  #L, #P, #V, #M
  INTR $1000
  RET
;OnKey1 :
{$D 727, 735}
{$E $01000021}
::OnKey1::
{$N 'OnKey1', 'L', 0}
  FUNC <OnKey1>
  PUSH #L, #F, #Q, #V, #M
  VAR  #L, 0
{$A True}
;if (Motor1.Active)
{$D 755, 773}
::OnKey1.1C::
  TYPE #W, (B:01)
  PORT #D, $0010 ;Motor1.Active
  EXTN #D, $002F ;getMotorActive
  RPOR #Q, #W, #D
  TST  #Q
  JOF  <OnKey1.1F>
::OnKey1.1T::
;Board.Led1 = LED_OFF;
{$D 784, 805}
  GET  #Q, 0 ;LED_OFF
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.LED1
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;Motor1.Active = false;
{$D 829, 851}
  GET  #Q, false
  TYPE #W, (B:01)
  PORT #D, $0010 ;Motor1.Active
  EXTN #D, $0030 ;setMotorActive
  WPOR #D, #W, #Q
;PrintLn("Motor1 is Deactive")
{$D 859, 888}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.8> ;"Motor1 is Deactive"
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::OnKey1.2.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
  JMP  <OnKey1.1X>
;else
{$D 898, 902}
::OnKey1.1F::
;Board.Led1 = LED_RED;
{$D 913, 934}
  GET  #Q, 2 ;LED_RED
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.LED1
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;Motor1.Active = true;
{$D 958, 979}
  GET  #Q, true
  TYPE #W, (B:01)
  PORT #D, $0010 ;Motor1.Active
  EXTN #D, $0030 ;setMotorActive
  WPOR #D, #W, #Q
;Motor1.Frequ = 10000;
{$D 1016, 1037}
  GET  #Q, 10000
  TYPE #W, (U:04)
  PORT #D, $0012 ;Motor1.Frequ
  EXTN #D, $0034 ;setMotorFrequ
  WPOR #D, #W, #Q
;Motor1.Speed = 80;
{$D 1078, 1096}
  GET  #Q, 80
  TYPE #W, (U:04)
  PORT #D, $0011 ;Motor1.Speed
  EXTN #D, $0032 ;setMotorSpeed
  WPOR #D, #W, #Q
;PrintLn("Motor1 is Active, Frequ = 10000, Speed = 80")
{$D 1104, 1158}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.9> ;"Motor1 is Active, Frequ = 10000, Speed = 80"
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::OnKey1.4.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
::OnKey1.1X::
{$D 1166, 1167}
::OnKey1.@::
{$A False}
  FREE #L
  POP  #L, #F, #Q, #V, #M
  IRET
;OnKey2 :
{$D 1209, 1217}
{$E $01000020}
::OnKey2::
{$N 'OnKey2', 'L', 0}
  FUNC <OnKey2>
  PUSH #L, #F, #Q, #X, #V, #M
  VAR  #L, 0
{$A True}
;if (! Motor1.Active)
{$D 1237, 1257}
::OnKey2.1C::
  TYPE #W, (B:01)
  PORT #D, $0010 ;Motor1.Active
  EXTN #D, $002F ;getMotorActive
  RPOR #Q, #W, #D
  NOT  #Q
  JOF  <OnKey2.1X>
::OnKey2.1T::
;return;
{$D 1258, 1265}
  JMP  <OnKey2.@>
::OnKey2.1X::
;if (Motor1.Polar == 0)
{$D 1271, 1293}
::OnKey2.2C::
  TYPE #W, (U:01)
  PORT #D, $0013 ;Motor1.Polar
  EXTN #D, $0035 ;getMotorPolar
  RPOR #Q, #W, #D
  GET  #X, 0
  EQU  #Q, #X
  JOF  <OnKey2.2F>
::OnKey2.2T::
;Board.Led1 = LED_BLUE;
{$D 1304, 1326}
  GET  #Q, 1 ;LED_BLUE
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.LED1
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;Motor1.Polar = 1;
{$D 1350, 1367}
  GET  #Q, 1
  TYPE #W, (U:01)
  PORT #D, $0013 ;Motor1.Polar
  EXTN #D, $0036 ;setMotorPolar
  WPOR #D, #W, #Q
;PrintLn("Motor1 is CCW, Polar = 1")
{$D 1375, 1410}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.10> ;"Motor1 is CCW, Polar = 1"
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::OnKey2.3.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
  JMP  <OnKey2.2X>
;else
{$D 1420, 1424}
::OnKey2.2F::
;Board.Led1 = LED_RED;
{$D 1435, 1456}
  GET  #Q, 2 ;LED_RED
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.LED1
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;Motor1.Polar = 0;
{$D 1480, 1497}
  GET  #Q, 0
  TYPE #W, (U:01)
  PORT #D, $0013 ;Motor1.Polar
  EXTN #D, $0036 ;setMotorPolar
  WPOR #D, #W, #Q
;PrintLn("Motor1 is CW, Polar = 0")
{$D 1505, 1539}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.11> ;"Motor1 is CW, Polar = 0"
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::OnKey2.5.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
::OnKey2.2X::
{$D 1547, 1548}
::OnKey2.@::
{$A False}
  FREE #L
  POP  #L, #F, #Q, #X, #V, #M
  IRET
;OnKey3 :
{$D 1590, 1598}
{$E $01000011}
::OnKey3::
{$N 'OnKey3', 'L', 0}
  FUNC <OnKey3>
  PUSH #L, #F, #Q, #V, #M
  VAR  #L, 0
{$A True}
;if (RetyFlag)
{$D 1618, 1631}
::OnKey3.1C::
  BASE #M, #G
  SEEK #M, $0000 ;RetyFlag
  TYPE #W, (B:01)
  LOAD #Q, #W, #M
  TST  #Q
  JOF  <OnKey3.1F>
::OnKey3.1T::
;RetyFlag = False;
{$D 1642, 1659}
  GET  #Q, False
  BASE #M, #G
  SEEK #M, $0000 ;RetyFlag
  TYPE #W, (B:01)
  SAVE #M, #W, #Q
;Board.RETY = RETY_OFF;
{$D 1693, 1715}
  GET  #Q, 0 ;RETY_OFF
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.RETY
  EXTN #D, $002B ;setGPIO
  WPOR #D, #W, #Q
;PrintLn("RETY set OFF")
{$D 1723, 1746}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.12> ;"RETY set OFF"
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::OnKey3.2.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
  JMP  <OnKey3.1X>
;else
{$D 1756, 1760}
::OnKey3.1F::
;RetyFlag = True;
{$D 1771, 1787}
  GET  #Q, True
  BASE #M, #G
  SEEK #M, $0000 ;RetyFlag
  TYPE #W, (B:01)
  SAVE #M, #W, #Q
;Board.RETY = RETY_ON;
{$D 1823, 1844}
  GET  #Q, 1 ;RETY_ON
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.RETY
  EXTN #D, $002B ;setGPIO
  WPOR #D, #W, #Q
;PrintLn("RETY set ON" )
{$D 1854, 1877}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.13> ;"RETY set ON"
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::OnKey3.4.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
::OnKey3.1X::
{$D 1885, 1886}
::OnKey3.@::
{$A False}
  FREE #L
  POP  #L, #F, #Q, #V, #M
  IRET
;OnKey4 :
{$D 1928, 1936}
{$E $01000010}
::OnKey4::
{$N 'OnKey4', 'L', 0}
  FUNC <OnKey4>
  PUSH #L, #F, #V, #M
  VAR  #L, 0
{$A True}
;PrintLn("Beep Test")
{$D 1956, 1976}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.14> ;"Beep Test"
  READ #V, #W, #D
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;PrintLn[1]:Text
  TYPE #W, (V:01)
  CAPI [&000006] ;PrintLn
::OnKey4.1.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
;Board.Beep(250, 3)
{$D 2023, 2041}
  VAR  #F, 3
  GET  #V, 250
  BASE #M, #F
  SEEK #M, $0001 ;Width
  TYPE #W, (U:01)
  SAVE #M, #W, #V ;Beep[1]:Width
  GET  #V, 3
  BASE #M, #F
  SEEK #M, $0002 ;Count
  TYPE #W, (U:01)
  SAVE #M, #W, #V ;Beep[2]:Count
  TYPE #W, (V:01)
  CAPI [&00002C] ;Beep
  FREE #F
{$D 2044, 2045}
::OnKey4.@::
{$A False}
  FREE #L
  POP  #L, #F, #V, #M
  IRET
;main
{$D 2049, 2053}
::main::
{$N 'main', 'P', 0}
{$N 'main', 'L', 2}
{$V 'Twise', $000000, 'U', 4, 0}
{$V 'OldTwise', $000004, 'U', 4, 0}
  FUNC <main>
  VAR  #P, 0
  VAR  #L, 8
{$A True}
;Welcome()
{$D 2060, 2069}
  VAR  #F, 1
  TYPE #W, (V:01)
  CALL <Welcome>
  FREE #F
;board.LED1 = LED_OFF;
{$D 2076, 2097}
  GET  #Q, 0 ;LED_OFF
  TYPE #W, (U:01)
  PORT #D, $0001 ;Board.LED1
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;board.LED2 = LED_OFF;
{$D 2101, 2122}
  GET  #Q, 0 ;LED_OFF
  TYPE #W, (U:01)
  PORT #D, $0002 ;Board.LED2
  EXTN #D, $0029 ;setLED
  WPOR #D, #W, #Q
;uint Twise = 0;
{$D 2150, 2165}
  GET  #Q, 0
  BASE #M, #L
  SEEK #M, $0000 ;Twise
  TYPE #W, (U:04)
  SAVE #M, #W, #Q
;uint OldTwise = 0;
{$D 2193, 2211}
  GET  #Q, 0
  BASE #M, #L
  SEEK #M, $0004 ;OldTwise
  TYPE #W, (U:04)
  SAVE #M, #W, #Q
;RetyFlag = False;
{$D 2274, 2291}
  GET  #Q, False
  BASE #M, #G
  SEEK #M, $0000 ;RetyFlag
  TYPE #W, (B:01)
  SAVE #M, #W, #Q
;OpenEvent()
{$D 2319, 2330}
  INTR $8000
  FREE #F
;repeat
{$D 2337, 2343}
::main.4L::
;Twise = Board.TWIST;
{$D 2392, 2412}
  TYPE #W, (U:02)
  PORT #D, $0001 ;Board.TWIST
  EXTN #D, $002A ;getSensor
  RPOR #Q, #W, #D
  BASE #M, #L
  SEEK #M, $0000 ;Twise
  TYPE #W, (U:04)
  SAVE #M, #W, #Q
;if ((Motor1.Active) && (Twise>0))
{$D 2463, 2496}
::main.5C::
  TYPE #W, (B:01)
  PORT #D, $0010 ;Motor1.Active
  EXTN #D, $002F ;getMotorActive
  RPOR #Q, #W, #D
  BASE #M, #L
  SEEK #M, $0000 ;Twise
  TYPE #W, (U:04)
  LOAD #X, #W, #M
  GET  #Y, 0
  GTN  #X, #Y
  AND  #Q, #X
  JOF  <main.5X>
::main.5T::
;if ((Twise +1 < OldTwise) || (Twise - 1 > OldTwise))
{$D 2603, 2655}
::main.6C::
  BASE #M, #L
  SEEK #M, $0000 ;Twise
  TYPE #W, (U:04)
  LOAD #Q, #W, #M
  GET  #X, 1
  ADD  #Q, #X
  BASE #M, #L
  SEEK #M, $0004 ;OldTwise
  TYPE #W, (U:04)
  LOAD #X, #W, #M
  LTN  #Q, #X
  BASE #M, #L
  SEEK #M, $0000 ;Twise
  TYPE #W, (U:04)
  LOAD #X, #W, #M
  GET  #Y, 1
  SUB  #X, #Y
  BASE #M, #L
  SEEK #M, $0004 ;OldTwise
  TYPE #W, (U:04)
  LOAD #Y, #W, #M
  GTN  #X, #Y
  ORR  #Q, #X
  JOF  <main.6X>
::main.6T::
;Motor1.Speed = Twise;
{$D 2712, 2733}
  BASE #M, #L
  SEEK #M, $0000 ;Twise
  TYPE #W, (U:04)
  LOAD #Q, #W, #M
  TYPE #W, (U:04)
  PORT #D, $0011 ;Motor1.Speed
  EXTN #D, $0032 ;setMotorSpeed
  WPOR #D, #W, #Q
;Print("Motor1 Speed = " # Twise #\n)
{$D 2743, 2779}
  VAR  #F, 5
  TYPE #W, (S:01)
  ADDR #D, <@DATA.15> ;"Motor1 Speed = "
  READ #V, #W, #D
  BASE #M, #L
  SEEK #M, $0000 ;Twise
  TYPE #W, (U:04)
  LOAD #X, #W, #M
  STRA #V, #X
  GET  #X, \n
  STRA #V, #X
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  SAVE #M, #W, #V ;Print[1]:Text
  TYPE #W, (V:01)
  CAPI [&000003] ;Print
::main.7.Text::
  BASE #M, #F
  SEEK #M, $0001 ;Text
  TYPE #W, (S:04)
  DEL  #M, #W
  FREE #F
;OldTwise = Twise;
{$D 2816, 2833}
  BASE #M, #L
  SEEK #M, $0000 ;Twise
  TYPE #W, (U:04)
  LOAD #Q, #W, #M
  BASE #M, #L
  SEEK #M, $0004 ;OldTwise
  TYPE #W, (U:04)
  SAVE #M, #W, #Q
::main.6X::
::main.5X::
;until error;
{$D 2858, 2870}
::main.4C::
  MOV  #Q, #E ;Global.Error
  TST  #Q
  JOF  <main.4L>
::main.4X::
;CloseEvent()
{$D 2900, 2912}
  INTR $0000
  FREE #F
{$D 2915, 2916}
::main.@::
{$A False}
  INTR $0000
  FREE #L
  FREE #P
  JMP  <@CRABSCRIPT.@>
