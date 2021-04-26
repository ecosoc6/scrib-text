# scrib-text
Export text from a Scribus desktop publishing .sla file.

Program Rationale:
------------------
The Scribus desktop publishing program ( https://www.scribus.net ) works pretty well but provides is no way to access the full text of the document all at once. It will export to .pdf but not plain text. Scribus provides access to text only for one frame (block of text) at a time, and a document typically consists of several, perhaps hundreds, of frames. Access to all of the text can be had by editing the .sla file, Scribus's native file format, with a text editor.  However, .sla is an XML format, and while human-readable is not *easily* human-readable if what you are interested in is to read the story text, because the story text is surrounded and interspersed with large amounts of code which sets the positioning, styles, etc. of the text.

This program removes the code part of the .sla file, producing a document  which contains only the story text.  While the output is not exactly polished, it is useful for spellchecking and searching the full story text. One can then go to Scribus or to the .sla file in a text editor, and make changes based on what one saw in the story text produced by this program.

Program Structure:
------------------

It's pretty simple. Source code is just a single file in C. See the comment at the beginning of the file for some more information. 
