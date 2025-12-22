



set val(chan) Channel/WirelessChannel ;# channel type
set val(prop) Propagation/TwoRayGround ;# radio-propagation model
set val(netif) Phy/WirelessPhy ;# network interface type
set val(mac) Mac/802_11 ;# MAC type
set val(ifq) Queue/DropTail/PriQueue ;# interface queue type
set val(ll) LL ;# link layer type
set val(ant) Antenna/OmniAntenna ;# antenna model
set val(ifqlen) 50 ;# max packet in ifq
set val(nn) 100 ;# number of mobilenodes
set val(rp) AODV;
set val(x) 1000 ;# X dimension of topography
set val(y) 1000 ;# Y dimension of topography
set val(stop) 100 ;# time of simulation end

set ns [new Simulator]
set tracefd [open out.tr w]
set namtrace [open out.nam w]

$ns trace-all $tracefd
$ns namtrace-all-wireless $namtrace $val(x) $val(y)

# set up topography object
set topo [new Topography]

$topo load_flatgrid $val(x) $val(y)

create-god $val(nn)



# configure the nodes
$ns node-config -adhocRouting $val(rp) \
-llType $val(ll) \
-macType $val(mac) \
-ifqType $val(ifq) \
-ifqLen $val(ifqlen) \
-antType $val(ant) \
-propType $val(prop) \
-phyType $val(netif) \
-channelType $val(chan) \
-topoInstance $topo \
-energyModel EnergyModel \
-initialEnergy 100 \
-txPower 0.9 \
-rxPower 0.8 \
-agentTrace ON \
-routerTrace ON \
-macTrace OFF \
-movementTrace ON

for {set i 0} {$i < $val(nn) } { incr i } {

set n($i) [$ns node]

}


proc createflow {src dst st et } {
global ns n
set tcp [new Agent/TCP/Newreno]
$tcp set class_ 2
set sink [new Agent/TCPSink]
$ns attach-agent $n($src) $tcp
$ns attach-agent $n($dst) $sink
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns at $st "$ftp start"
$ns at $et "$ftp stop"
}



#===================================
#    	Agents Definition   	 
#===================================
#Setup a UDP connection
set udp0 [new Agent/UDP]
$ns attach-agent $n(4) $udp0
set null1 [new Agent/Null]
$ns attach-agent $n(18) $null1
$ns connect $udp0 $null1
$udp0 set packetSize_ 1500

#Setup a CBR Application over UDP connection
set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$cbr0 set packetSize_ 1000
$cbr0 set rate_ 0.3Mb
$cbr0 set random_ null
$ns at 1.0 "$cbr0 start"
$ns at 80.0 "$cbr0 stop"


#Setup a UDP connection
set udp1 [new Agent/UDP]
$ns attach-agent $n(8) $udp1
set null2 [new Agent/Null]
$ns attach-agent $n(18) $null2
$ns connect $udp1 $null1
$udp1 set packetSize_ 1500

#Setup a CBR Application over UDP connection
set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set packetSize_ 1000
$cbr1 set rate_ 0.3Mb
$cbr1 set random_ null
$ns at 1.0 "$cbr1 start"
$ns at 80.0 "$cbr1 stop"


#Setup a UDP connection
set udp3 [new Agent/UDP]
$ns attach-agent $n(9) $udp3
set null3 [new Agent/Null]
$ns attach-agent $n(18) $null3
$ns connect $udp3 $null1
$udp3 set packetSize_ 1500

#Setup a CBR Application over UDP connection
set cbr2 [new Application/Traffic/CBR]
$cbr2 attach-agent $udp3
$cbr2 set packetSize_ 1000
$cbr2 set rate_ 0.3Mb
$cbr2 set random_ null
$ns at 1.0 "$cbr2 start"
$ns at 80.0 "$cbr2 stop"


set udp4 [new Agent/UDP]
$ns attach-agent $n(10) $udp4
set null4 [new Agent/Null]
$ns attach-agent $n(18) $null4
$ns connect $udp4 $null4
$udp4 set packetSize_ 1500

#Setup a CBR Application over UDP connection
set cbr4 [new Application/Traffic/CBR]
$cbr4 attach-agent $udp4
$cbr4 set packetSize_ 1000
$cbr4 set rate_ 0.3Mb
$cbr4 set random_ null
$ns at 1.0 "$cbr4 start"
$ns at 80.0 "$cbr4 stop"

$ns at 0.01 "$n(18) label \"Destination\""
$ns at 0.01 "$n(18) add-mark m2 red circle"

$ns at 40.01 "$n(4) label \"selfish\""
$ns at 40.01 "$n(4) add-mark m2 blue circle"



source grid

set hmac [new Agent/hmac]

$hmac set E1 40
$hmac set E2 50 
$hmac set E3 60
$hmac set E4 70
$hmac set S1 32
$hmac set S2 18
$hmac set S3 45
$hmac set S4 55
$hmac set FC 10
$ns at 6.0 "$hmac initiate"

$ns at 0.01 "$n(40) label \"Tag1\""
$ns at 0.01 "$n(40) add-mark m2 brown square"

$ns at 0.01 "$n(50) label \"Tag2\""
$ns at 0.01 "$n(50) add-mark m2 blue square"

$ns at 0.01 "$n(60) label \"Tag3\""
$ns at 0.01 "$n(60) add-mark m2 black square"

$ns at 0.01 "$n(70) label \"Tag4\""
$ns at 0.01 "$n(70) add-mark m2 brown square"

$ns at 0.01 "$n(32) label \"SN1\""
$ns at 0.01 "$n(32) add-mark m2 pink square"

$ns at 0.01 "$n(18) label \"SN2\""
$ns at 0.01 "$n(18) add-mark m2 yellow square"

$ns at 0.01 "$n(45) label \"SN3\""
$ns at 0.01 "$n(45) add-mark m2 pink square"

$ns at 0.01 "$n(55) label \"SN4\""
$ns at 0.01 "$n(55) add-mark m2 yellow square"

$ns at 0.01 "$n(52) label \"RFID\""
$ns at 0.01 "$n(52) add-mark m2 red square"


$ns at 0.01 "$n(51) label \"READER\""
$ns at 0.01 "$n(51) add-mark m2 red square"

$ns at 0.01 "$n(16) label \"READER\""
$ns at 0.01 "$n(16) add-mark m2 red square"

$ns at 0.01 "$n(58) label \"READER\""
$ns at 0.01 "$n(58) add-mark m2 red square"

$ns at 0.01 "$n(87) label \"READER\""
$ns at 0.01 "$n(58) add-mark m2 red square"


$ns at 10 " $n(40) setdest 50 250 20 "
$ns at 50 " $n(40) setdest 150 350 20 "
$ns at 70 " $n(40) setdest 50 150 20 "

$ns at 10 " $n(50) setdest 75 150 20 "
$ns at 40 " $n(50) setdest 170 80 20 "
$ns at 50 " $n(50) setdest 250 120 20 "
$ns at 70 " $n(50) setdest 350 410 20 "

$ns at 10 " $n(60) setdest 67 150 20 "
$ns at 50 " $n(60) setdest 230 430 20 "
$ns at 70 " $n(60) setdest 420 250 20 "

$ns at 10 " $n(70) setdest 35 210 20 "
$ns at 50 " $n(70) setdest 410 350 20 "
$ns at 70 " $n(70) setdest 150 370 20 "



# Define node initial position in nam
for {set i 0} {$i < $val(nn)} { incr i } {
# 20 defines the node size for nam
if {$i != 9} {
$ns initial_node_pos $n($i) 20
}
}
$ns initial_node_pos $n(9) 40

$ns initial_node_pos $n(40) 40
$ns initial_node_pos $n(50) 40
$ns initial_node_pos $n(60) 40
$ns initial_node_pos $n(70) 40
$ns initial_node_pos $n(32) 40
$ns initial_node_pos $n(18) 40
$ns initial_node_pos $n(45) 40
$ns initial_node_pos $n(55) 40

$ns at 0.0 "$ns trace-annotate \"Generating ECC private key, 1024 bit long modulus\""

for {set j 0} {$j < $val(nn) } { incr j } {

set pval [ expr { round(rand() * 999) } ]
set qval [ expr { round(rand() * 99) } ]


$ns at 0.0 "$ns trace-annotate \"Generating ECC private key, 1024 bit long modulus\""
$ns at 0.3450 "$ns trace-annotate \"Node ID :: $pval :: Password :: $qval\""
puts "Generating ECC private key, 1024 bit long modulus"
exec openssl genrsa -out keys/$n($j).pem 1024-rand &

$ns at 0.3455 "$n($j) label \"$pval :: $qval\""
puts "Node Identity :: $pval :: Password :: $qval"


}

# Telling nodes when the simulation ends
for {set i 0} {$i < $val(nn) } { incr i } {
$ns at $val(stop) "$n($i) reset";
}

# ending nam and the simulation
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "stop"
$ns at 100.01 "puts \"end simulation\" ; $ns halt"
proc stop {} {
global ns tracefd namtrace
$ns flush-trace
close $tracefd
close $namtrace

}

$ns run
