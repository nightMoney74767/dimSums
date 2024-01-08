<h1>DimSums</h1>
This project contains the files for a C++ project that allows users to play a console-based version of Dim Sums, a minigame from the TV programme Richard Osman's House of Games. 
The project uses Boost libraries and consists of a client and a server, both of which are separate processes and send data back and forth. The following rules apply:
<ul>
  <li>Four, six or eight clues will appear, depending on the chosen difficulty</li>
  <li>Each clue is associated with a number which the users will need to work out</li>
  <li>Two clues will be selected and the sum of their values will make up a target number</li>
  <li>To win, the user must select two clues, the sum of which is equal the target number</li>
</ul>
To run this project on your device, please follow these steps:
<ol>
  <li>download the code from this repository</li>
  <li>for Windows:</li>
  <ul>
    <li>download and run the installer for <a href="https://visualstudio.microsoft.com/downloads/">Visual Studio</a>. The community edition is available for free. When asked, select the c++ workload and click install</li>
    <li>visit the website for <a href="https://www.boost.org/users/download/">Boost</a> and select either the 7z or ZIP file</li>
    <li>extract the arhcive then open either the Command Prompt or Powershell (you can also use the Windows Terminal) and go to the directory where the archive was extracted (e.g., cd C:\Boost)</li>
    <li>run the <code>bootstrap</code> script. Once finished, run <code>.\b2</code></li>
    <li>download the project code and open the .sln file in Visual Studio</li>
    <li>in the solution explorer, right-click the Client folder and select properties</li>
    <li>select the C/C++ option in the left pane of the properties window. Set the additional include directories to point to the location of the Boost libraries (e.g., C:\Boost\boost_1_81_0\boost_1_81_0)</li>
    <li>click apply then go to the linker option in the left pane. Set the additional library directories to point to the same directory but with the addition of "\stage\lib"</li>
    <li>repeat the last two steps for the server</li>
    <li>to run both the client and server at the same time, click the drop-down arrow next to the "Local Windows Debugger" button and choose "configure startup projects". Click the "multiple projects" option and set both the client and server to start with or without debugging</li>
    <li>select the start button</li>
  </ul>
  <li>for macOS and Linux</li>
  <ul>
    <li>visit the website for <a href="https://www.boost.org/users/download/">Boost</a> and select either the TAR.GZ or the TAR.BZ2 file</li>
    <li>using an appropriate utility, extract the archive</li>
    <li>open a terminal and go to the directory where the libraries were extracted</li>
    <li>run the <code>bootstrap</code> script. Once finished, run <code>./b2</code></li>
    <li>compile the code in an IDE of your choice. Make sure the Boost libraries are included</li>
  </ul>
</ol>
