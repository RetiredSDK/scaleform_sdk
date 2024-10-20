#! /usr/bin/env perl

# Program for testing regular expressions with perl to check that PCRE handles
# them the same. This is the version that supports /8 for UTF-8 testing. As it
# stands, it requires at least Perl 5.8 for UTF-8 support. However, it needs to
# have "use utf8" at the start for running the UTF-8 tests, but *not* for the
# other tests. The only way I've found for doing this is to cat this line in
# explicitly in the RunPerlTest script.

# use locale;  # With this included, \x0b matches \s!

# Function for turning a string into a string of printing chars. There are
# currently problems with UTF-8 strings; this fudges round them.

sub pchars {
my($t) = "";

if ($utf8)
  {
  @p = unpack('U*', $_[0]);
  foreach $c (@p)
    {
    if ($c >= 32 && $c < 127) { $t .= chr $c; }
      else { $t .= sprintf("\\x{%02x}", $c); }
    }
  }

else
  {
  foreach $c (split(//, $_[0]))
    {
    if (ord $c >= 32 && ord $c < 127) { $t .= $c; }
      else { $t .= sprintf("\\x%02x", ord $c); }
    }
  }

$t;
}


# Read lines from named file or stdin and write to named file or stdout; lines
# consist of a regular expression, in delimiters and optionally followed by
# options, followed by a set of test data, terminated by an empty line.

# Sort out the input and output files

if (@ARGV > 0)
  {
  open(INFILE, "<$ARGV[0]") || die "Failed to open $ARGV[0]\n";
  $infile = "INFILE";
  }
else { $infile = "STDIN"; }

if (@ARGV > 1)
  {
  open(OUTFILE, ">$ARGV[1]") || die "Failed to open $ARGV[1]\n";
  $outfile = "OUTFILE";
  }
else { $outfile = "STDOUT"; }

printf($outfile "Perl $] Regular Expressions\n\n");

# Main loop

NEXT_RE:
for (;;)
  {
  printf "  re> " if $infile eq "STDIN";
  last if ! ($_ = <$infile>);
  printf $outfile "$_" if $infile ne "STDIN";
  next if ($_ eq "");

  $pattern = $_;

  while ($pattern !~ /^\s*(.).*\1/s)
    {
    printf "    > " if $infile eq "STDIN";
    last if ! ($_ = <$infile>);
    printf $outfile "$_" if $infile ne "STDIN";
    $pattern .= $_;
    }

   chomp($pattern);
   $pattern =~ s/\s+$//;

  # The private /+ modifier means "print $' afterwards".

  $showrest = ($pattern =~ s/\+(?=[a-zA-Z]*$)//);

  # A doubled version is used by pcretest to print remainders after captures

  $pattern =~ s/\+(?=[a-zA-Z]*$)//;

  # Remove /8 from a UTF-8 pattern.

  $utf8 = $pattern =~ s/8(?=[a-zA-Z]*$)//;

  # Remove /J from a pattern with duplicate names.

  $pattern =~ s/J(?=[a-zA-Z]*$)//;

  # Remove /K from a pattern (asks pcretest to check MARK data) */

  $pattern =~ s/K(?=[a-zA-Z]*$)//;

  # Remove /W from a pattern (asks pcretest to set PCRE_UCP)

  $pattern =~ s/W(?=[a-zA-Z]*$)//;

  # Remove /S or /SS from a pattern (asks pcretest to study or not to study)

  $pattern =~ s/S(?=[a-zA-Z]*$)//g;

  # Remove /Y from a pattern (asks pcretest to disable PCRE optimization)

  $pattern =~ s/Y(?=[a-zA-Z]*$)//;

  # Check that the pattern is valid

  eval "\$_ =~ ${pattern}";
  if ($@)
    {
    printf $outfile "Error: $@";
    next NEXT_RE;
    }

  # If the /g modifier is present, we want to put a loop round the matching;
  # otherwise just a single "if".

  $cmd = ($pattern =~ /g[a-z]*$/)? "while" : "if";

  # If the pattern is actually the null string, Perl uses the most recently
  # executed (and successfully compiled) regex is used instead. This is a
  # nasty trap for the unwary! The PCRE test suite does contain null strings
  # in places - if they are allowed through here all sorts of weird and
  # unexpected effects happen. To avoid this, we replace such patterns with
  # a non-null pattern that has the same effect.

  $pattern = "/(?#)/$2" if ($pattern =~ /^(.)\1(.*)$/);

  # Read data lines and test them

  for (;;)
    {
    printf "data> " if $infile eq "STDIN";
    last NEXT_RE if ! ($_ = <$infile>);
    chomp;
    printf $outfile "$_\n" if $infile ne "STDIN";

    s/\s+$//;  # Remove trailing space
    s/^\s+//;  # Remove leading space
    s/\\Y//g;  # Remove \Y (pcretest flag to set PCRE_NO_START_OPTIMIZE)

    last if ($_ eq "");
    $x = eval "\"$_\"";   # To get escapes processed

    # Empty array for holding results, ensure $REGERROR and $REGMARK are
    # unset, then do the matching.

    @subs = ();

    $pushes = "push \@subs,\$&;" .
         "push \@subs,\$1;" .
         "push \@subs,\$2;" .
         "push \@subs,\$3;" .
         "push \@subs,\$4;" .
         "push \@subs,\$5;" .
         "push \@subs,\$6;" .
         "push \@subs,\$7;" .
         "push \@subs,\$8;" .
         "push \@subs,\$9;" .
         "push \@subs,\$10;" .
         "push \@subs,\$11;" .
         "push \@subs,\$12;" .
         "push \@subs,\$13;" .
         "push \@subs,\$14;" .
         "push \@subs,\$15;" .
         "push \@subs,\$16;" .
         "push \@subs,\$'; }";

    undef $REGERROR;
    undef $REGMARK;

    eval "${cmd} (\$x =~ ${pattern}) {" . $pushes;

    if ($@)
      {
      printf $outfile "Error: $@\n";
      next NEXT_RE;
      }
    elsif (scalar(@subs) == 0)
      {
      printf $outfile "No match";
      if (defined $REGERROR && $REGERROR != 1)
        { print $outfile (", mark = $REGERROR"); }
      printf $outfile "\n";
      }
    else
      {
      while (scalar(@subs) != 0)
        {
        printf $outfile (" 0: %s\n", &pchars($subs[0]));
        printf $outfile (" 0+ %s\n", &pchars($subs[17])) if $showrest;
        $last_printed = 0;
        for ($i = 1; $i <= 16; $i++)
          {
          if (defined $subs[$i])
            {
            while ($last_printed++ < $i-1)
              { printf $outfile ("%2d: <unset>\n", $last_printed); }
            printf $outfile ("%2d: %s\n", $i, &pchars($subs[$i]));
            $last_printed = $i;
            }
          }
        splice(@subs, 0, 18);
        }
      if (defined $REGMARK && $REGMARK != 1)
        { print $outfile ("MK: $REGMARK\n"); }
      }
    }
  }

# printf $outfile "\n";

# End
