#!/usr/bin/perl

$flag = "STCTF#5aRcAmMa5573R15Wa7Ch1NGY0u#";
$qrCodeCounter = 0;

&generateQrCodes;
&injectLSB;
&tarball;


sub generateQrCodes {
    $b64 = `base64 sarcasm.jpg -w 1990`;

    @lines = split /\n/, $b64;
    $i = 0;

    foreach (@lines) {
        $i++;
        $qrString = $i . ":{" . $_ . "}";
        `qr --factory=pymaging $qrString > qr$i.png`;
    }
    $qrCodeCounter = $i;
}

sub injectLSB {
    foreach $i (1..$qrCodeCounter) {
        `perl lsbtool.pl -i qr$i.png -o qr$i.png -b 1 -ch red -c $flag`;
    }
}

sub tarball {
    $files = "";

    foreach $i (1..$qrCodeCounter) {
        $files = $files . "qr$i.png ";
    }
    print $files; 
    `tar -cvzf sarcasm.tar.gz $files --remove-files`;
}
