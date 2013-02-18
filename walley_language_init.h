//
//  walley_language_init.h
//  Walley
//
//  Created by shd101wyy on 12-11-6.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

#include "walley_class.h"
// load __walley_language__.wy __walley_verb__.wy __walley_similarity__.wy
// All of those file are in 'brain_path'
void Walley_Load_Brain(char *brain_path,char *walley_language_file_name,char*walley_language_similarity_file_name,char*walley_language_verb_file_name){
    
    brain_path=toCString(brain_path);
    WALLEY_LANGUAGE_FILE=(char**)malloc(sizeof(char*)*10000);
    WALLEY_SIMILARITY_FILE=(char**)malloc(sizeof(char*)*10000);
    WALLEY_VERB_FILE=(char**)malloc(sizeof(char*)*4000);
    BRAIN_PATH=brain_path;
    
    // Walley_Language_Default_File......
    /*
     :|:|
     CREATE FILE VAR|CREATE_FILE ( VAR )|
     DEF AN IDEA CALLED VAR WITH VAR :|DEF VAR ( VAR ) :|
     DEF VAR ( VAR ) :|DEF VAR ( VAR ) :|
     DEF VAR :|DEF VAR :|
     DEFINE A FUNCTION CALLED VAR WITH PARAMETERS VAR :|DEF VAR ( VAR ) :|
     DEFINE A FUNCTION CALLED VAR WITH ROW VAR AND COLUMN VAR :|DEF VAR ( VAR , VAR ) :|
     DEFINE A KIND OF OBJECT CALLED VAR :|CLASS VAR :|
     DEFINE IDEA CALLED VAR WITH PARAMETERS VAR AND VAR|DEF VAR ( VAR , VAR ) :|
     DEFINE VAR ( SELF , VAR )|DEF VAR ( SELF , VAR ) :|
     DEFINE VAR ( VAR ) :|DEF VAR ( VAR ) :|
     DEFINE VAR WITH VAR :|DEF VAR ( VAR ) :|
     DEFINE VAR WITH VAR AS A FUNCTION|DEF VAR ( VAR ) :|
     DEFINE VAR WITH VAR AS FUNCTION :|DEF VAR ( VAR ) :|
     DEFINE VAR WITH VAR|DEF VAR ( VAR ) :|
     DELETE FILE VAR|REMOVE_FILE ( VAR )|
     FOR VAR IN VAR :|FOR VAR IN VAR :|
     FOR VAR IN VAR|FOR VAR IN VAR :|
     FROM VAR IMPORT VAR AS VAR|FROM VAR IMPORT VAR AS VAR|
     FROM VAR IMPORT VAR|FROM VAR IMPORT VAR|
     IF VAR :|IF VAR :|
     IF VAR EQUALS VAR :|IF VAR == VAR :|
     IMPORT VAR AS VAR|IMPORT VAR AS VAR|
     IMPORT VAR|IMPORT VAR|
     IN|IN|
     PRINT ( VAR )|PRINT ( VAR )|eg print ( "Hello" )----->print ("Hello")|
     PRINT OUT VAR|PRINT VAR|
     PRINT VALUE OF VAR|PRINT ( VAR )|
     PRINT VAR ( VAR )|PRINT ( VAR ( VAR ) )|
     PRINT VAR|PRINT ( VAR )|eg print "Hello"----->print ( "Hello" )|
     PRINTLN ( VAR )|PRINTLN ( VAR )|
     PRINTLN VAR|PRINTLN ( VAR )|
     PRINTS VAR|PRINT ( VAR )|
     RETURN VAR ( VAR )|RETURN VAR ( VAR )|
     RETURN VAR|RETURN VAR|
     VAR ( VAR )|VAR ( VAR )|
     VAR = FUNCTION ( VAR )|VAR = FUNCTION ( VAR )|
     VAR = FUNCTION WITH VAR|VAR = FUNCTION ( VAR )|
     VAR = VAR|VAR = VAR|
     VAR EQUAL VAR|VAR = VAR|
     VAR EQUALS VAR ( VAR )|VAR = VAR ( VAR )|
     VAR EQUALS VAR|VAR = VAR|eg x equals 12----->x = 12|
     VAR IS A KIND OF VAR1|VAR IS VAR1 ( )|
     VAR IS MATRIX WITH ROW VAR AND COLUMN VAR|VAR = MATRIX ( VAR , VAR )|
     VAR IS MATRIX WITH ROW VAR COLUMN VAR|VAR = MATRIX ( VAR , VAR )|
     VAR IS MONTH|VAR = MONTH()|
     VAR IS TEXT FROM VAR|VAR = FILE_READLINES ( VAR )|
     VAR IS TIME|VAR = TIME ( )|
     VAR IS VAR ( VAR )|VAR = VAR ( VAR )|
     VAR IS VAR OF VAR1 AND VAR2|VAR = VAR ( VAR1 , VAR2 )|
     VAR IS VAR WITH VAR|VAR = VAR ( VAR )|
     VAR IS VAR|VAR = VAR|
     VAR TOLOWER|VAR.TOLOWER()|
     VAR TOUPPER()|VAR.TOUPPER()|
     VAR TOUPPER|VAR.TOUPPER()|
     VAR|VAR|
     WHAT TIME IS IT NOW|PRINT(TIME())|
     WHILE VAR :|WHILE VAR :|
     WRITE VAR1 TO VAR2|FILE_WRITELINES (STR ( VAR2 ) + "," + STR ( VAR1 ) )|
     */
    // Walley_Langauge_Verb_File......
    /*
     #~
     # change ####| to ####|
     # VERB #
     import:
     imports:
     def:
     define:
     defines:
     is:
     are:
     was:
     were:
     accept:
     care:
     could:
     enjoy:
     equals:
     equal:
     happen:
     lead:
     open:
     reduce:
     settle:
     teach:
     account:
     carry:
     count:
     examine:
     hate:
     learn:
     order:
     refer:
     shake:
     tell:
     achieve:
     catch:
     cover:
     exist:
     have:
     leave:
     ought:
     reflect:
     shall:
     tend:
     act:
     cause:
     create:
     expect:
     head:
     lend:
     own:
     refuse:
     share:
     test:
     add:
     change:
     cross:
     experience:
     hear:
     let:
     pass:
     regard:
     shoot:
     thank:
     admit:
     charge:
     cry:
     explain:
     help:
     lie:
     pay:
     relate:
     should:
     think:
     affect:
     check:
     cut:
     express:
     hide:
     like:
     perform:
     release:
     shout:
     throw:
     afford:
     choose:
     damage:
     extend:
     hit:
     limit:
     pick:
     remain:
     show:
     touch:
     agree:
     claim:
     dance:
     face:
     hold:
     link:
     place:
     remember:
     shut:
     train:
     aim:
     clean:
     deal:
     fail:
     hope:
     listen:
     plan:
     remove:
     sing:
     travel:
     allow:
     clear:
     decide:
     fall:
     hurt:
     live:
     play:
     repeat:
     sit:
     treat:
     answer:
     climb:
     deliver:
     fasten:
     identify:
     look:
     point:
     replace:
     sleep:
     try:
     appear:
     close:
     demand:
     feed:
     imagine:
     lose:
     prefer:
     reply:
     smile:
     turn:
     apply:
     collect:
     deny:
     feel:
     improve:
     love:
     prepare:
     report:
     sort:
     understand:
     argue:
     come:
     depend:
     fight:
     include:
     make:
     present:
     represent:
     sound:
     use:
     arrange:
     commit:
     describe:
     fill:
     increase:
     manage:
     press:
     require:
     speak:
     used to:
     arrive:
     compare:
     design:
     find:
     indicate:
     mark:
     prevent:
     rest:
     stand:
     visit:
     ask:
     complain:
     destroy:
     finish:
     influence:
     matter:
     produce:
     result:
     start:
     vote:
     attack:
     complete:
     develop:
     fit:
     inform:
     may:
     promise:
     return:
     state:
     wait:
     avoid:
     concern:
     die:
     fly:
     intend:
     mean:
     protect:
     reveal:
     stay:
     walk:
     base:
     confirm:
     disappear:
     fold:
     introduce:
     measure:
     prove:
     ring:
     stick:
     want:
     be:
     connect:
     discover:
     follow:
     invite:
     meet:
     provide:
     rise:
     stop:
     warn:
     beat:
     consider:
     discuss:
     force:
     involve:
     mention:
     publish:
     roll:
     study:
     wash:
     become:
     consist:
     divide:
     forget:
     join:
     might:
     pull:
     run:
     succeed:
     watch:
     begin:
     contact:
     do:
     forgive:
     jump:
     mind:
     push:
     save:
     suffer:
     wear:
     believe:
     contain:
     draw:
     form:
     keep:
     miss:
     put:
     say:
     suggest:
     will:
     belong:
     continue:
     dress:
     found:
     kick:
     move:
     raise:
     see:
     suit:
     win:
     break:
     contribute:
     drink:
     gain:
     kill:
     must:
     reach:
     seem:
     supply:
     wish:
     build:
     control:
     drive:
     get:
     knock:
     need:
     read:
     sell:
     support:
     wonder:
     burn:
     cook:
     drop:
     give:
     know:
     notice:
     realize:
     send:
     suppose:
     work:
     buy:
     copy:
     eat:
     go:
     last:
     obtain:
     receive:
     separate:
     survive:
     worry:
     call:
     correct:
     enable:
     grow:
     laugh:
     occur:
     recognize:
     serve:
     take:
     would:
     can:
     cost:
     encourage:
     handle:
     lay:
     offer:
     record:
     set:
     talk:
     write:
     print:
     prints:
     println:
     
     # Proverbs #
     in:
     at:
     on:
     with:
     to:
     from:
     before:
     after:
     of:
     for:
     as:

     */
    // Walley_Language_Similarity_File......
    /*
     #~
     # in order to make 'define circle with radius as a function'
     # format to 'DEFINE VAR WITH VAR AS A FUNCTION'
     # by judge the similarity and assign one particular value about similarity
     # to judge whether I could make translation
     # put longer sentence ahead….
     # e.g., the first below… Only when similarity is 5 while the sentences be translated
     DEFINE A FUNCTION CALLED VAR WITH ROW VAR AND COLUMN VAR :|9|
     DEFINE A FUNCTION CALLED VAR WITH PARAMETERS VAR :|7|
     DEFINE A VAR WITH VAR AS A FUNCTION|6|
     DEFINE VAR ( SELF , VAR )|5|
     DEFINE VAR WITH VAR AS A FUNCTION|5|
     DEF A VAR WITH VAR AS A FUNCTION|6|
     DEF VAR WITH VAR AS A FUNCTION|5|
     WHAT TIME IS IT NOW|5|
     VAR IS MATRIX WITH ROW VAR AND COLUMN VAR|6|
     PRINT VALUE OF VAR|3|
     VAR = VAR|1|
     VAR IS TEXT FROM VAR|3|
     CREATE FILE VAR|2|
     DELETE FILE VAR|2|
     DEFINE IDEA CALLED VAR WITH PARAMETERS VAR AND VAR|6|
     VAR IS VAR OF VAR1 AND VAR2|3|
     VAR IS MONTH|2|
     VAR IS TIME|2|
     WRITE VAR1 TO VAR2|2|
     DEF AN IDEA CALLED VAR WITH VAR :|6|
     DEFINE A KIND OF OBJECT CALLED VAR :|7|
     VAR IS A KIND OF VAR1|4|
     
     */
    
    // load Walley_Language_Default_File......

    int index=0;
    WALLEY_LANGUAGE_FILE[index]=":|:|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="CLASS VAR :|CLASS VAR :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="CREATE FILE VAR|CREATE_FILE ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEF AN IDEA CALLED VAR WITH VAR :|DEF VAR ( VAR ) :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEF VAR ( VAR ) :|DEF VAR ( VAR ) :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEF VAR :|DEF VAR :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEFINE A FUNCTION CALLED VAR WITH PARAMETERS VAR :|DEF VAR ( VAR ) :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEFINE A FUNCTION CALLED VAR WITH ROW VAR AND COLUMN VAR :|DEF VAR ( VAR , VAR ) :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEFINE A KIND OF OBJECT CALLED VAR :|CLASS VAR :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEFINE IDEA CALLED VAR WITH PARAMETERS VAR AND VAR|DEF VAR ( VAR , VAR ) :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEFINE VAR ( SELF , VAR )|DEF VAR ( SELF , VAR ) :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEFINE VAR ( VAR ) :|DEF VAR ( VAR ) :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEFINE VAR WITH VAR :|DEF VAR ( VAR ) :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEFINE VAR WITH VAR AS A FUNCTION|DEF VAR ( VAR ) :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEFINE VAR WITH VAR AS FUNCTION :|DEF VAR ( VAR ) :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DEFINE VAR WITH VAR|DEF VAR ( VAR ) :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="DELETE FILE VAR|REMOVE_FILE ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="FOR VAR IN VAR :|FOR VAR IN VAR :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="FOR VAR IN VAR|FOR VAR IN VAR :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="FROM VAR IMPORT VAR AS VAR|FROM VAR IMPORT VAR AS VAR|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="FROM VAR IMPORT VAR|FROM VAR IMPORT VAR|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="IF VAR :|IF VAR :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="IF VAR EQUALS VAR :|IF VAR == VAR :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="IMPORT VAR AS VAR|IMPORT VAR AS VAR|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="IMPORT VAR|IMPORT VAR|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="IN|IN|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="PRINT ( VAR )|PRINT ( VAR )|eg print ( \"Hello\" )----->print (\"Hello\")|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="PRINT OUT VAR|PRINT VAR|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="PRINT VALUE OF VAR|PRINT ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="PRINT VAR ( VAR )|PRINT ( VAR ( VAR ) )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="PRINT VAR|PRINT ( VAR )|eg print \"Hello\"----->print ( \"Hello\" )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="PRINTLN ( VAR )|PRINTLN ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="PRINTLN VAR|PRINTLN ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="PRINTS VAR|PRINT ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="RETURN VAR ( VAR )|RETURN VAR ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="RETURN VAR|RETURN VAR|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR ( VAR )|VAR ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR = FUNCTION ( VAR )|VAR = FUNCTION ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR = FUNCTION WITH VAR|VAR = FUNCTION ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR = VAR|VAR = VAR|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR EQUAL VAR|VAR = VAR|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR EQUALS VAR ( VAR )|VAR = VAR ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR EQUALS VAR|VAR = VAR|eg x equals 12----->x = 12|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR IS A KIND OF VAR1|VAR IS VAR1 ( )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR IS MATRIX WITH ROW VAR AND COLUMN VAR|VAR = MATRIX ( VAR , VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR IS MATRIX WITH ROW VAR COLUMN VAR|VAR = MATRIX ( VAR , VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR IS MONTH|VAR = MONTH()|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR IS TEXT FROM VAR|VAR = FILE_READLINES ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR IS TIME|VAR = TIME ( )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR IS VAR ( VAR )|VAR = VAR ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR IS VAR OF VAR1 AND VAR2|VAR = VAR ( VAR1 , VAR2 )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR IS VAR WITH VAR|VAR = VAR ( VAR )|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR IS VAR|VAR = VAR|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR TOLOWER|VAR.TOLOWER()|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR TOUPPER()|VAR.TOUPPER()|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR TOUPPER|VAR.TOUPPER()|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="VAR|VAR|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="WHAT TIME IS IT NOW|PRINT(TIME())|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="WHILE VAR :|WHILE VAR :|";index+=1;
    WALLEY_LANGUAGE_FILE[index]="WRITE VAR1 TO VAR2|FILE_WRITELINES (STR ( VAR2 ) + \",\" + STR ( VAR1 ) )|";index+=1;
    
    int index_of_walley_language_file=index;
    
//############### load verb default file ##########################################
//#~
//# change ####| to ####|
//# VERB #
    index=0;
    WALLEY_VERB_FILE[index]="import:";index+=1;
    WALLEY_VERB_FILE[index]="imports:";index+=1;
    WALLEY_VERB_FILE[index]="def:";index+=1;
    WALLEY_VERB_FILE[index]="define:";index+=1;
    WALLEY_VERB_FILE[index]="defines:";index+=1;
    WALLEY_VERB_FILE[index]="is:";index+=1;
    WALLEY_VERB_FILE[index]="are:";index+=1;
    WALLEY_VERB_FILE[index]="was:";index+=1;
    WALLEY_VERB_FILE[index]="were:";index+=1;
    WALLEY_VERB_FILE[index]="accept:";index+=1;
    WALLEY_VERB_FILE[index]="care:";index+=1;
    WALLEY_VERB_FILE[index]="could:";index+=1;
    WALLEY_VERB_FILE[index]="enjoy:";index+=1;
    WALLEY_VERB_FILE[index]="equals:";index+=1;
    WALLEY_VERB_FILE[index]="equal:";index+=1;
    WALLEY_VERB_FILE[index]="happen:";index+=1;
    WALLEY_VERB_FILE[index]="lead:";index+=1;
    WALLEY_VERB_FILE[index]="open:";index+=1;
    WALLEY_VERB_FILE[index]="reduce:";index+=1;
    WALLEY_VERB_FILE[index]="settle:";index+=1;
    WALLEY_VERB_FILE[index]="teach:";index+=1;
    WALLEY_VERB_FILE[index]="account:";index+=1;
    WALLEY_VERB_FILE[index]="carry:";index+=1;
    WALLEY_VERB_FILE[index]="count:";index+=1;
    WALLEY_VERB_FILE[index]="examine:";index+=1;
    WALLEY_VERB_FILE[index]="hate:";index+=1;
    WALLEY_VERB_FILE[index]="learn:";index+=1;
    WALLEY_VERB_FILE[index]="order:";index+=1;
    WALLEY_VERB_FILE[index]="refer:";index+=1;
    WALLEY_VERB_FILE[index]="shake:";index+=1;
    WALLEY_VERB_FILE[index]="tell:";index+=1;
    WALLEY_VERB_FILE[index]="achieve:";index+=1;
    WALLEY_VERB_FILE[index]="catch:";index+=1;
    WALLEY_VERB_FILE[index]="cover:";index+=1;
    WALLEY_VERB_FILE[index]="exist:";index+=1;
    WALLEY_VERB_FILE[index]="have:";index+=1;
    WALLEY_VERB_FILE[index]="leave:";index+=1;
    WALLEY_VERB_FILE[index]="ought:";index+=1;
    WALLEY_VERB_FILE[index]="reflect:";index+=1;
    WALLEY_VERB_FILE[index]="shall:";index+=1;
    WALLEY_VERB_FILE[index]="tend:";index+=1;
    WALLEY_VERB_FILE[index]="act:";index+=1;
    WALLEY_VERB_FILE[index]="cause:";index+=1;
    WALLEY_VERB_FILE[index]="create:";index+=1;
    WALLEY_VERB_FILE[index]="expect:";index+=1;
    WALLEY_VERB_FILE[index]="head:";index+=1;
    WALLEY_VERB_FILE[index]="lend:";index+=1;
    WALLEY_VERB_FILE[index]="own:";index+=1;
    WALLEY_VERB_FILE[index]="refuse:";index+=1;
    WALLEY_VERB_FILE[index]="share:";index+=1;
    WALLEY_VERB_FILE[index]="test:";index+=1;
    WALLEY_VERB_FILE[index]="add:";index+=1;
    WALLEY_VERB_FILE[index]="change:";index+=1;
    WALLEY_VERB_FILE[index]="cross:";index+=1;
    WALLEY_VERB_FILE[index]="experience:";index+=1;
    WALLEY_VERB_FILE[index]="hear:";index+=1;
    WALLEY_VERB_FILE[index]="let:";index+=1;
    WALLEY_VERB_FILE[index]="pass:";index+=1;
    WALLEY_VERB_FILE[index]="regard:";index+=1;
    WALLEY_VERB_FILE[index]="shoot:";index+=1;
    WALLEY_VERB_FILE[index]="thank:";index+=1;
    WALLEY_VERB_FILE[index]="admit:";index+=1;
    WALLEY_VERB_FILE[index]="charge:";index+=1;
    WALLEY_VERB_FILE[index]="cry:";index+=1;
    WALLEY_VERB_FILE[index]="explain:";index+=1;
    WALLEY_VERB_FILE[index]="help:";index+=1;
    WALLEY_VERB_FILE[index]="lie:";index+=1;
    WALLEY_VERB_FILE[index]="pay:";index+=1;
    WALLEY_VERB_FILE[index]="relate:";index+=1;
    WALLEY_VERB_FILE[index]="should:";index+=1;
    WALLEY_VERB_FILE[index]="think:";index+=1;
    WALLEY_VERB_FILE[index]="affect:";index+=1;
    WALLEY_VERB_FILE[index]="check:";index+=1;
    WALLEY_VERB_FILE[index]="cut:";index+=1;
    WALLEY_VERB_FILE[index]="express:";index+=1;
    WALLEY_VERB_FILE[index]="hide:";index+=1;
    WALLEY_VERB_FILE[index]="like:";index+=1;
    WALLEY_VERB_FILE[index]="perform:";index+=1;
    WALLEY_VERB_FILE[index]="release:";index+=1;
    WALLEY_VERB_FILE[index]="shout:";index+=1;
    WALLEY_VERB_FILE[index]="throw:";index+=1;
    WALLEY_VERB_FILE[index]="afford:";index+=1;
    WALLEY_VERB_FILE[index]="choose:";index+=1;
    WALLEY_VERB_FILE[index]="damage:";index+=1;
    WALLEY_VERB_FILE[index]="extend:";index+=1;
    WALLEY_VERB_FILE[index]="hit:";index+=1;
    WALLEY_VERB_FILE[index]="limit:";index+=1;
    WALLEY_VERB_FILE[index]="pick:";index+=1;
    WALLEY_VERB_FILE[index]="remain:";index+=1;
    WALLEY_VERB_FILE[index]="show:";index+=1;
    WALLEY_VERB_FILE[index]="touch:";index+=1;
    WALLEY_VERB_FILE[index]="agree:";index+=1;
    WALLEY_VERB_FILE[index]="claim:";index+=1;
    WALLEY_VERB_FILE[index]="dance:";index+=1;
    WALLEY_VERB_FILE[index]="face:";index+=1;
    WALLEY_VERB_FILE[index]="hold:";index+=1;
    WALLEY_VERB_FILE[index]="link:";index+=1;
    WALLEY_VERB_FILE[index]="place:";index+=1;
    WALLEY_VERB_FILE[index]="remember:";index+=1;
    WALLEY_VERB_FILE[index]="shut:";index+=1;
    WALLEY_VERB_FILE[index]="train:";index+=1;
    WALLEY_VERB_FILE[index]="aim:";index+=1;
    WALLEY_VERB_FILE[index]="clean:";index+=1;
    WALLEY_VERB_FILE[index]="deal:";index+=1;
    WALLEY_VERB_FILE[index]="fail:";index+=1;
    WALLEY_VERB_FILE[index]="hope:";index+=1;
    WALLEY_VERB_FILE[index]="listen:";index+=1;
    WALLEY_VERB_FILE[index]="plan:";index+=1;
    WALLEY_VERB_FILE[index]="remove:";index+=1;
    WALLEY_VERB_FILE[index]="sing:";index+=1;
    WALLEY_VERB_FILE[index]="travel:";index+=1;
    WALLEY_VERB_FILE[index]="allow:";index+=1;
    WALLEY_VERB_FILE[index]="clear:";index+=1;
    WALLEY_VERB_FILE[index]="decide:";index+=1;
    WALLEY_VERB_FILE[index]="fall:";index+=1;
    WALLEY_VERB_FILE[index]="hurt:";index+=1;
    WALLEY_VERB_FILE[index]="live:";index+=1;
    WALLEY_VERB_FILE[index]="play:";index+=1;
    WALLEY_VERB_FILE[index]="repeat:";index+=1;
    WALLEY_VERB_FILE[index]="sit:";index+=1;
    WALLEY_VERB_FILE[index]="treat:";index+=1;
    WALLEY_VERB_FILE[index]="answer:";index+=1;
    WALLEY_VERB_FILE[index]="climb:";index+=1;
    WALLEY_VERB_FILE[index]="deliver:";index+=1;
    WALLEY_VERB_FILE[index]="fasten:";index+=1;
    WALLEY_VERB_FILE[index]="identify:";index+=1;
    WALLEY_VERB_FILE[index]="look:";index+=1;
    WALLEY_VERB_FILE[index]="point:";index+=1;
    WALLEY_VERB_FILE[index]="replace:";index+=1;
    WALLEY_VERB_FILE[index]="sleep:";index+=1;
    WALLEY_VERB_FILE[index]="try:";index+=1;
    WALLEY_VERB_FILE[index]="appear:";index+=1;
    WALLEY_VERB_FILE[index]="close:";index+=1;
    WALLEY_VERB_FILE[index]="demand:";index+=1;
    WALLEY_VERB_FILE[index]="feed:";index+=1;
    WALLEY_VERB_FILE[index]="imagine:";index+=1;
    WALLEY_VERB_FILE[index]="lose:";index+=1;
    WALLEY_VERB_FILE[index]="prefer:";index+=1;
    WALLEY_VERB_FILE[index]="reply:";index+=1;
    WALLEY_VERB_FILE[index]="smile:";index+=1;
    WALLEY_VERB_FILE[index]="turn:";index+=1;
    WALLEY_VERB_FILE[index]="apply:";index+=1;
    WALLEY_VERB_FILE[index]="collect:";index+=1;
    WALLEY_VERB_FILE[index]="deny:";index+=1;
    WALLEY_VERB_FILE[index]="feel:";index+=1;
    WALLEY_VERB_FILE[index]="improve:";index+=1;
    WALLEY_VERB_FILE[index]="love:";index+=1;
    WALLEY_VERB_FILE[index]="prepare:";index+=1;
    WALLEY_VERB_FILE[index]="report:";index+=1;
    WALLEY_VERB_FILE[index]="sort:";index+=1;
    WALLEY_VERB_FILE[index]="understand:";index+=1;
    WALLEY_VERB_FILE[index]="argue:";index+=1;
    WALLEY_VERB_FILE[index]="come:";index+=1;
    WALLEY_VERB_FILE[index]="depend:";index+=1;
    WALLEY_VERB_FILE[index]="fight:";index+=1;
    WALLEY_VERB_FILE[index]="include:";index+=1;
    WALLEY_VERB_FILE[index]="make:";index+=1;
    WALLEY_VERB_FILE[index]="present:";index+=1;
    WALLEY_VERB_FILE[index]="represent:";index+=1;
    WALLEY_VERB_FILE[index]="sound:";index+=1;
    WALLEY_VERB_FILE[index]="use:";index+=1;
    WALLEY_VERB_FILE[index]="arrange:";index+=1;
    WALLEY_VERB_FILE[index]="commit:";index+=1;
    WALLEY_VERB_FILE[index]="describe:";index+=1;
    WALLEY_VERB_FILE[index]="fill:";index+=1;
    WALLEY_VERB_FILE[index]="increase:";index+=1;
    WALLEY_VERB_FILE[index]="manage:";index+=1;
    WALLEY_VERB_FILE[index]="press:";index+=1;
    WALLEY_VERB_FILE[index]="require:";index+=1;
    WALLEY_VERB_FILE[index]="speak:";index+=1;
    WALLEY_VERB_FILE[index]="used to:";index+=1;
    WALLEY_VERB_FILE[index]="arrive:";index+=1;
    WALLEY_VERB_FILE[index]="compare:";index+=1;
    WALLEY_VERB_FILE[index]="design:";index+=1;
    WALLEY_VERB_FILE[index]="find:";index+=1;
    WALLEY_VERB_FILE[index]="indicate:";index+=1;
    WALLEY_VERB_FILE[index]="mark:";index+=1;
    WALLEY_VERB_FILE[index]="prevent:";index+=1;
    WALLEY_VERB_FILE[index]="rest:";index+=1;
    WALLEY_VERB_FILE[index]="stand:";index+=1;
    WALLEY_VERB_FILE[index]="visit:";index+=1;
    WALLEY_VERB_FILE[index]="ask:";index+=1;
    WALLEY_VERB_FILE[index]="complain:";index+=1;
    WALLEY_VERB_FILE[index]="destroy:";index+=1;
    WALLEY_VERB_FILE[index]="finish:";index+=1;
    WALLEY_VERB_FILE[index]="influence:";index+=1;
    WALLEY_VERB_FILE[index]="matter:";index+=1;
    WALLEY_VERB_FILE[index]="produce:";index+=1;
    WALLEY_VERB_FILE[index]="result:";index+=1;
    WALLEY_VERB_FILE[index]="start:";index+=1;
    WALLEY_VERB_FILE[index]="vote:";index+=1;
    WALLEY_VERB_FILE[index]="attack:";index+=1;
    WALLEY_VERB_FILE[index]="complete:";index+=1;
    WALLEY_VERB_FILE[index]="develop:";index+=1;
    WALLEY_VERB_FILE[index]="fit:";index+=1;
    WALLEY_VERB_FILE[index]="inform:";index+=1;
    WALLEY_VERB_FILE[index]="may:";index+=1;
    WALLEY_VERB_FILE[index]="promise:";index+=1;
    WALLEY_VERB_FILE[index]="return:";index+=1;
    WALLEY_VERB_FILE[index]="state:";index+=1;
    WALLEY_VERB_FILE[index]="wait:";index+=1;
    WALLEY_VERB_FILE[index]="avoid:";index+=1;
    WALLEY_VERB_FILE[index]="concern:";index+=1;
    WALLEY_VERB_FILE[index]="die:";index+=1;
    WALLEY_VERB_FILE[index]="fly:";index+=1;
    WALLEY_VERB_FILE[index]="intend:";index+=1;
    WALLEY_VERB_FILE[index]="mean:";index+=1;
    WALLEY_VERB_FILE[index]="protect:";index+=1;
    WALLEY_VERB_FILE[index]="reveal:";index+=1;
    WALLEY_VERB_FILE[index]="stay:";index+=1;
    WALLEY_VERB_FILE[index]="walk:";index+=1;
    WALLEY_VERB_FILE[index]="base:";index+=1;
    WALLEY_VERB_FILE[index]="confirm:";index+=1;
    WALLEY_VERB_FILE[index]="disappear:";index+=1;
    WALLEY_VERB_FILE[index]="fold:";index+=1;
    WALLEY_VERB_FILE[index]="introduce:";index+=1;
    WALLEY_VERB_FILE[index]="measure:";index+=1;
    WALLEY_VERB_FILE[index]="prove:";index+=1;
    WALLEY_VERB_FILE[index]="ring:";index+=1;
    WALLEY_VERB_FILE[index]="stick:";index+=1;
    WALLEY_VERB_FILE[index]="want:";index+=1;
    WALLEY_VERB_FILE[index]="be:";index+=1;
    WALLEY_VERB_FILE[index]="connect:";index+=1;
    WALLEY_VERB_FILE[index]="discover:";index+=1;
    WALLEY_VERB_FILE[index]="follow:";index+=1;
    WALLEY_VERB_FILE[index]="invite:";index+=1;
    WALLEY_VERB_FILE[index]="meet:";index+=1;
    WALLEY_VERB_FILE[index]="provide:";index+=1;
    WALLEY_VERB_FILE[index]="rise:";index+=1;
    WALLEY_VERB_FILE[index]="stop:";index+=1;
    WALLEY_VERB_FILE[index]="warn:";index+=1;
    WALLEY_VERB_FILE[index]="beat:";index+=1;
    WALLEY_VERB_FILE[index]="consider:";index+=1;
    WALLEY_VERB_FILE[index]="discuss:";index+=1;
    WALLEY_VERB_FILE[index]="force:";index+=1;
    WALLEY_VERB_FILE[index]="involve:";index+=1;
    WALLEY_VERB_FILE[index]="mention:";index+=1;
    WALLEY_VERB_FILE[index]="publish:";index+=1;
    WALLEY_VERB_FILE[index]="roll:";index+=1;
    WALLEY_VERB_FILE[index]="study:";index+=1;
    WALLEY_VERB_FILE[index]="wash:";index+=1;
    WALLEY_VERB_FILE[index]="become:";index+=1;
    WALLEY_VERB_FILE[index]="consist:";index+=1;
    WALLEY_VERB_FILE[index]="divide:";index+=1;
    WALLEY_VERB_FILE[index]="forget:";index+=1;
    WALLEY_VERB_FILE[index]="join:";index+=1;
    WALLEY_VERB_FILE[index]="might:";index+=1;
    WALLEY_VERB_FILE[index]="pull:";index+=1;
    WALLEY_VERB_FILE[index]="run:";index+=1;
    WALLEY_VERB_FILE[index]="succeed:";index+=1;
    WALLEY_VERB_FILE[index]="watch:";index+=1;
    WALLEY_VERB_FILE[index]="begin:";index+=1;
    WALLEY_VERB_FILE[index]="contact:";index+=1;
    WALLEY_VERB_FILE[index]="do:";index+=1;
    WALLEY_VERB_FILE[index]="does";index+=1;
    WALLEY_VERB_FILE[index]="forgive:";index+=1;
    WALLEY_VERB_FILE[index]="jump:";index+=1;
    WALLEY_VERB_FILE[index]="mind:";index+=1;
    WALLEY_VERB_FILE[index]="push:";index+=1;
    WALLEY_VERB_FILE[index]="save:";index+=1;
    WALLEY_VERB_FILE[index]="suffer:";index+=1;
    WALLEY_VERB_FILE[index]="wear:";index+=1;
    WALLEY_VERB_FILE[index]="believe:";index+=1;
    WALLEY_VERB_FILE[index]="contain:";index+=1;
    WALLEY_VERB_FILE[index]="draw:";index+=1;
    WALLEY_VERB_FILE[index]="form:";index+=1;
    WALLEY_VERB_FILE[index]="keep:";index+=1;
    WALLEY_VERB_FILE[index]="miss:";index+=1;
    WALLEY_VERB_FILE[index]="put:";index+=1;
    WALLEY_VERB_FILE[index]="say:";index+=1;
    WALLEY_VERB_FILE[index]="suggest:";index+=1;
    WALLEY_VERB_FILE[index]="will:";index+=1;
    WALLEY_VERB_FILE[index]="belong:";index+=1;
    WALLEY_VERB_FILE[index]="continue:";index+=1;
    WALLEY_VERB_FILE[index]="dress:";index+=1;
    WALLEY_VERB_FILE[index]="found:";index+=1;
    WALLEY_VERB_FILE[index]="kick:";index+=1;
    WALLEY_VERB_FILE[index]="move:";index+=1;
    WALLEY_VERB_FILE[index]="raise:";index+=1;
    WALLEY_VERB_FILE[index]="see:";index+=1;
    WALLEY_VERB_FILE[index]="suit:";index+=1;
    WALLEY_VERB_FILE[index]="win:";index+=1;
    WALLEY_VERB_FILE[index]="break:";index+=1;
    WALLEY_VERB_FILE[index]="contribute:";index+=1;
    WALLEY_VERB_FILE[index]="drink:";index+=1;
    WALLEY_VERB_FILE[index]="gain:";index+=1;
    WALLEY_VERB_FILE[index]="kill:";index+=1;
    WALLEY_VERB_FILE[index]="must:";index+=1;
    WALLEY_VERB_FILE[index]="reach:";index+=1;
    WALLEY_VERB_FILE[index]="seem:";index+=1;
    WALLEY_VERB_FILE[index]="supply:";index+=1;
    WALLEY_VERB_FILE[index]="wish:";index+=1;
    WALLEY_VERB_FILE[index]="build:";index+=1;
    WALLEY_VERB_FILE[index]="control:";index+=1;
    WALLEY_VERB_FILE[index]="drive:";index+=1;
    WALLEY_VERB_FILE[index]="get:";index+=1;
    WALLEY_VERB_FILE[index]="knock:";index+=1;
    WALLEY_VERB_FILE[index]="need:";index+=1;
    WALLEY_VERB_FILE[index]="read:";index+=1;
    WALLEY_VERB_FILE[index]="sell:";index+=1;
    WALLEY_VERB_FILE[index]="support:";index+=1;
    WALLEY_VERB_FILE[index]="wonder:";index+=1;
    WALLEY_VERB_FILE[index]="burn:";index+=1;
    WALLEY_VERB_FILE[index]="cook:";index+=1;
    WALLEY_VERB_FILE[index]="drop:";index+=1;
    WALLEY_VERB_FILE[index]="give:";index+=1;
    WALLEY_VERB_FILE[index]="know:";index+=1;
    WALLEY_VERB_FILE[index]="notice:";index+=1;
    WALLEY_VERB_FILE[index]="realize:";index+=1;
    WALLEY_VERB_FILE[index]="send:";index+=1;
    WALLEY_VERB_FILE[index]="suppose:";index+=1;
    WALLEY_VERB_FILE[index]="work:";index+=1;
    WALLEY_VERB_FILE[index]="buy:";index+=1;
    WALLEY_VERB_FILE[index]="copy:";index+=1;
    WALLEY_VERB_FILE[index]="eat:";index+=1;
    WALLEY_VERB_FILE[index]="go:";index+=1;
    WALLEY_VERB_FILE[index]="last:";index+=1;
    WALLEY_VERB_FILE[index]="obtain:";index+=1;
    WALLEY_VERB_FILE[index]="receive:";index+=1;
    WALLEY_VERB_FILE[index]="separate:";index+=1;
    WALLEY_VERB_FILE[index]="survive:";index+=1;
    WALLEY_VERB_FILE[index]="worry:";index+=1;
    WALLEY_VERB_FILE[index]="call:";index+=1;
    WALLEY_VERB_FILE[index]="correct:";index+=1;
    WALLEY_VERB_FILE[index]="enable:";index+=1;
    WALLEY_VERB_FILE[index]="grow:";index+=1;
    WALLEY_VERB_FILE[index]="laugh:";index+=1;
    WALLEY_VERB_FILE[index]="occur:";index+=1;
    WALLEY_VERB_FILE[index]="recognize:";index+=1;
    WALLEY_VERB_FILE[index]="serve:";index+=1;
    WALLEY_VERB_FILE[index]="take:";index+=1;
    WALLEY_VERB_FILE[index]="would:";index+=1;
    WALLEY_VERB_FILE[index]="can:";index+=1;
    WALLEY_VERB_FILE[index]="cost:";index+=1;
    WALLEY_VERB_FILE[index]="encourage:";index+=1;
    WALLEY_VERB_FILE[index]="handle:";index+=1;
    WALLEY_VERB_FILE[index]="lay:";index+=1;
    WALLEY_VERB_FILE[index]="offer:";index+=1;
    WALLEY_VERB_FILE[index]="record:";index+=1;
    WALLEY_VERB_FILE[index]="set:";index+=1;
    WALLEY_VERB_FILE[index]="talk:";index+=1;
    WALLEY_VERB_FILE[index]="write:";index+=1;
    WALLEY_VERB_FILE[index]="print:";index+=1;
    WALLEY_VERB_FILE[index]="prints:";index+=1;
    WALLEY_VERB_FILE[index]="println:";index+=1;

    //# Proverbs #
    WALLEY_VERB_FILE[index]="in:";index+=1;
    WALLEY_VERB_FILE[index]="at:";index+=1;
    WALLEY_VERB_FILE[index]="on:";index+=1;
    WALLEY_VERB_FILE[index]="with:";index+=1;
    WALLEY_VERB_FILE[index]="to:";index+=1;
    WALLEY_VERB_FILE[index]="from:";index+=1;
    WALLEY_VERB_FILE[index]="before:";index+=1;
    WALLEY_VERB_FILE[index]="after:";index+=1;
    WALLEY_VERB_FILE[index]="of:";index+=1;
    WALLEY_VERB_FILE[index]="for:";index+=1;
    WALLEY_VERB_FILE[index]="as:";index+=1;

    int index_of_walley_language_verb_file=index;
    //########### load Walley_Similarity_File #############
//#~
//# in order to make 'define circle with radius as a function'
//# format to 'DEFINE VAR WITH VAR AS A FUNCTION'
//# by judge the similarity and assign one particular value about similarity
//# to judge whether I could make translation
//# put longer sentence ahead….
//# e.g., the first below… Only when similarity is 5 while the sentences be translated
    
    index=0;
    WALLEY_SIMILARITY_FILE[index]="DEFINE A FUNCTION CALLED VAR WITH ROW VAR AND COLUMN VAR :|9|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="DEFINE A FUNCTION CALLED VAR WITH PARAMETERS VAR :|7|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="DEFINE A VAR WITH VAR AS A FUNCTION|6|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="DEFINE VAR ( SELF , VAR )|5|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="DEFINE VAR WITH VAR AS A FUNCTION|5|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="DEF A VAR WITH VAR AS A FUNCTION|6|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="DEF VAR WITH VAR AS A FUNCTION|5|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="WHAT TIME IS IT NOW|5|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="VAR IS MATRIX WITH ROW VAR AND COLUMN VAR|6|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="PRINT VALUE OF VAR|3|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="VAR = VAR|1|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="VAR IS TEXT FROM VAR|3|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="CREATE FILE VAR|2|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="DELETE FILE VAR|2|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="DEFINE IDEA CALLED VAR WITH PARAMETERS VAR AND VAR|6|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="VAR IS VAR OF VAR1 AND VAR2|3|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="VAR IS MONTH|2|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="VAR IS TIME|2|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="WRITE VAR1 TO VAR2|2|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="DEF AN IDEA CALLED VAR WITH VAR :|6|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="DEFINE A KIND OF OBJECT CALLED VAR :|7|";index+=1;
    WALLEY_SIMILARITY_FILE[index]="VAR IS A KIND OF VAR1|4|";index+=1;
    int index_of_walley_similarity_file=index;

    
    
    
    //################# Code Before ###############//
    
    if (brain_path[(int)strlen(brain_path)-1]!='/') {
        brain_path=append(brain_path, "/");
    }
    /*
    char *walley_language_file=append(brain_path, "__walley_language__.wy");
    char *walley_language_similarity_file=append(brain_path, "__walley_language_similarity__.wy");
    char *walley_ver_file=append(brain_path, "__walley_language_verb__.wy");
     */
    char *walley_language_file=append(brain_path, walley_language_file_name);
    char *walley_language_similarity_file=append(brain_path, walley_language_similarity_file_name);
    char *walley_ver_file=append(brain_path, walley_language_verb_file_name);

    FILE *fp;
    char arr[10000]="";
    int row=0;
    // Load user Walley_Language_File
    fp=fopen(walley_language_file, "r");
    if (fp==NULL) {
        //printf("did not find user walley language file\n");
       // printf("FILE %s NOT FOUND\n",walley_language_file);
       // exit(0);
    } else {
    
        while (fgets(arr, 10000, fp)!=NULL) {
            char *temp=append("",arr);
            temp=removeNFromBack(temp);
            if (stringIsEmpty(temp)==TRUE ||temp[0]=='#') {
                continue;
            }
            WALLEY_LANGUAGE_FILE[index_of_walley_language_file]=temp;
            index_of_walley_language_file++;
        }
    }
    fclose(fp);
    row=0;
    
    
    // Load user Walley_Similarity_File
    fp=fopen(walley_language_similarity_file, "r");
    if (fp==NULL) {
       // printf("FILE %s NOT FOUND\n",walley_language_similarity_file);
       // exit(0);
        //printf("did not find user walley language similarity file\n");

    }else{
        while (fgets(arr, 10000, fp)!=NULL) {
            char *temp=append("",arr);
            temp=removeNFromBack(temp);
            if (stringIsEmpty(temp)==TRUE ||temp[0]=='#') {
                continue;
            }
            WALLEY_SIMILARITY_FILE[index_of_walley_similarity_file]=temp;
            index_of_walley_similarity_file++;
        }
    }
    fclose(fp);
    row=0;
    
    // Load user Walley_Verb_File
    fp=fopen(walley_ver_file, "r");
    if (fp==NULL) {
       // printf("FILE %s NOT FOUND\n",walley_ver_file);
       // exit(0);
        //printf("did not find user walley language verb file\n");

    }else{
        while (fgets(arr, 10000, fp)!=NULL) {
            char *temp=append("",arr);
            temp=removeNFromBack(temp);
            if (stringIsEmpty(temp)==TRUE ||temp[0]=='#') {
                continue;
            }
            WALLEY_VERB_FILE[index_of_walley_language_verb_file]=temp;
            index_of_walley_language_verb_file++;
        }
    }
    fclose(fp);
}

void Walley_Finalize_Brain(){
    free(WALLEY_LANGUAGE_FILE);
    free(WALLEY_SIMILARITY_FILE);
    free(WALLEY_VERB_FILE);
}