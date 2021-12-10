# Contacts
desktop application and website to keep your data safe and easy to access
## Desktop Application
qt6 c++<br>
download instructions...
## Website
frontend: vanilla js<br>
backend: modified lamp stack (qt6 c++ replacing php)<br>site linked
<a href="http://jakehenryparker.com:56112/Contacts/"> here</a>
## Storage
everything is stored remotely on maria db<br>
if you only have 1 login and your data will be synced between the desktop app and website
## Encryption
when you enter your password the first thing done to it is a ton of sha3_256 hashing, then it is stored in either cookies or <a href="https://doc.qt.io/qt-5/qsettings.html">qsettings</a> as your <a href="https://www.atpinc.com/blog/what-is-aes-256-encryption">aes256</a> key, then it is hashed a ton more before being sent across the internet<br><br>all your contacts information is encrypted and decrypted with your aes key
