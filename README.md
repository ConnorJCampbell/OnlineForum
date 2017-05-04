# OnlineForum

********************
Incomplete Features:
********************

- marking "all" as read
Marking all as read will work with an individual stream, but not with all.

- Order toggle
The viewing program will only list streams in the order they are ordered in the database:
by date added. You cannot toggle between date and username.


*******************
Additional Notes:
*******************
- Whenever my db program is executed, I create the necessary tables for the program.
- Authors can be multiple words, but streams ca only be a single word.
- If the user does not enter a username, it will default to "GUEST".
- When the post program is run and the stream does not exist, the user will simply be prompted to use the
  addauthor option.
- A post cannot be more than 10,000 characters.
- Apostrophies can usually be entered into a message without a problem, though I have found a few special cases
  such as adding two apostrophies at the end of an entry can cause problems.
- Usernames and streams cannot contain apostrophies.
- Usernames, streams and posts cannot contain quotes. If you want to include a quote in a post, you should use an escape
  character. For example: \"Hello\" 
- When the user hits "mark all as read" while viewing a single stream, the view program will print out the last post in the stream.
- When the user views all streams or hits check for new or mark all while viewing all streams, the view program will return to the first
  post.
- I attempted to catch as many errors as I could on my own and produce meaningful error messages, but sometimes
  I will just print out an SQL error. For example, when you try to add an author to a stream that they already have
  access to, the program will not allow it and tell you that you are entering a dublicate primary key. This doesn't
  break the program in any way, it just isn't as nice to read.

Viewing "all" bug:
- If you hit last while viewing the final post, or next while viewing the first post(after hitting previous),
  the program will skip over the second last or last post, respectively. For this reason, if a user only has access to
  3 total posts and you view them through all, you will most likely be unable to view the second post.


******************************
Notes regarding the SQL flags
******************************
- I assume that all the flags listed in the spec will be run from the command line, so the output is
  formatted to fit that environment.
- I also assume that each of the flags will only be run one at a time. For example, "./db -users" or 
  "./db -reset", entering a second arguement will only run the first one. For example, "./db -streams posts"
  will only print out the streams.
- Each line printed out with the -user flag will display a username and a stream that they have access to.
  Therefore, there may be multiple duplicate usernames displayed.
