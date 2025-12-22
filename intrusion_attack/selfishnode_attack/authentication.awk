BEGIN {
        sendLine = 0;
        recvLine = 0;
        fowardLine = 0;
}
 
$0 ~/^s.* AGT/ {
        sendLine ++ ;
}
 
$0 ~/^r.* AGT/ {
        recvLine ++ ;
}
 
$0 ~/^f.* RTR/ {
        fowardLine ++ ;
}
 
END {
        printf "cbr Packets Sent = %d\nAuthorized Packets = %d\nAuthentication Ratio = %.4f\nForward Security = %d \n", sendLine, recvLine, (recvLine/sendLine),fowardLine;
}
