# multiuservirtualdiary
<h1 align="center">📖 Digital Diary Application</h1>
<h3 align="center">Secure Personal Journaling Solution with Modern UI</h3>

<div align="center">
  <img src="https://img.shields.io/badge/License-MIT-blue.svg">
  <img src="https://img.shields.io/badge/GTK-3.0+-orange.svg">
  <img src="https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-green.svg">
</div>

<h2>✨ Features</h2>

<h3>🔒 Authentication System</h3>
<ul>
  <li>📛 Secure username/password validation</li>
  <li>🔑 Encrypted credential storage</li>
  <li>🚫 Duplicate user prevention</li>
</ul>

<h3>📓 Diary Management</h3>
<ul>
  <li>⏰ Automatic entry timestamping</li>
  <li>📜 Scrollable history view</li>
  <li>💾 Persistent local storage</li>
</ul>

<h3>🛡️ Security</h3>
<ul>
  <li>🔐 File permission hardening (chmod 600)</li>
  <li>🧹 Complete data purge on logout</li>
  <li>✅ Input sanitization</li>
</ul>

<h3>🎨 UI/UX</h3>
<ul>
  <li>🌈 Animated gradient backgrounds</li>
  <li>📝 Ruled paper styling</li>
  <li>💅 Modern CSS animations</li>
</ul>

<h2>🚀 Technical Stack</h2>
<table>
  <tr>
    <th>Component</th>
    <th>Technology</th>
  </tr>
  <tr>
    <td>GUI Framework</td>
    <td>GTK3+</td>
  </tr>
  <tr>
    <td>Storage</td>
    <td>Flat-file system</td>
  </tr>
  <tr>
    <td>Security</td>
    <td>POSIX file permissions</td>
  </tr>
</table>

<h2>📦 Installation</h2>
<pre>
<code># Dependencies
sudo apt-get install build-essential libgtk-3-dev

# Compilation
gcc main.c -o diary-app `pkg-config --cflags --libs gtk+-3.0`

# Execution
./diary-app</code>
</pre>

<h2>🔗 License</h2>
<p>MIT License - Free for personal and commercial use</p>
<div align="center">
  <a href="LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-blue.svg">
  </a>
</div>
