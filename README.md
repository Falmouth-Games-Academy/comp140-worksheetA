#### Improved word choosing algorithm pseudocode  
while **word_options** has less than 15 words:  
    > get random word from **word** list  
    > check **word**'s likeness and compare it to a tally.  
    > ***if*** there are already a few words of the same likeness, dont add **word** to > the options  
    > ***if not***, add **word** to the list of **word_options** and add to the tally  
    > (this is so there doesnt end up with 10 words all of 0 likeness, only 3/4 at most.)  
