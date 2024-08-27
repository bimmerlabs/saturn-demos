#!/usr/bin/perl
use strict;
use warnings;

# this pre-sorts the palette by the blue channel, which can then be sorted by hand from there.
# input is JASC-PAL (256 colors) .pal file
# Initialize arrays to store RGB values and "255 255 255" values separately 
# because we assume the 256th color will be transparent if it is white
my $table = [];
my $white_table = [];
# Open the JASC-PAL file for reading
open my $fh, '<', 'C:\temp\Normal Map\NormalWheel_512_unsorted.pal' or die "Cannot open palette.pal: $!";

# Read and store the first three lines (header)
my @header;
push @header, scalar <$fh> for 1..3;

# Read the remaining lines (RGB values)
while (my $line = <$fh>) {
    chomp $line;
    my @rgb = split ' ', $line;
    if ( $line eq ('255 255 255')) {
        push @$white_table, \@rgb;  # Store "255 255 255" separately
    } else {
        push @$table, \@rgb;  # Store other RGB values
    }
}

close $fh;

# Sort the $table by R (ascending), G (descending), B (descending)
$table = [
    sort {
       $b->[2] <=> $a->[2]   # Sort by B (descending)
        || $b->[0] <=> $a->[0]      # Sort by R (ascending)
        || $b->[1] <=> $a->[1]   # Sort by G (descending) (does nothing)
    } @$table
];

# Open the output file for writing
open my $out, '>', 'C:\temp\Normal Map\pre-sorted.pal' or die "Cannot open sorted.pal: $!";

# Write the header to the output file
print $out @header;

# Write the sorted RGB values to the output file
foreach my $rgb (@$table) {
    print $out join(' ', @$rgb), "\n";
}

# Write the "255 255 255" values to the end of the file
foreach my $rgb (@$white_table) {
    print $out join(' ', @$rgb), "\n";
}

close $out;

print "The sorted palette has been saved to sorted.pal.\n";