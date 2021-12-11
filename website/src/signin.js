var onload = function() {
    // check cookies and shit
    SignUpFrame();
    HashThis("jake", 1000);
}

function SignUpFrame() {
    let sPage = "";
    sPage += "<div class='si'>";
    sPage += "<div class='si_text si_header'>Sign Up</div>";
    sPage += "<div id='feedback' class='si_text si_subHead'>to continue to site</div>";
    sPage += "<div class='si_innerContainer'>";
    sPage += "<input id='username' type='input' class='si_textBox' placeholder='Username' maxlength=15 title='username' />";
    sPage += "<input id='password' type='password' class='si_textBox' placeholder='Password' title='password' />";
    sPage += "<input id='confirm' type='password' class='si_textBox' placeholder='Confirm Password' title='confirm password' />";
    sPage += "<div id='Memory' class='si_text si_subHead si_checkbox' onClick='toggleMemory()' title='green remembers you'>Remember Me</div>";
    sPage += "<button class='si_textBox si_button' onClick='createAccount()'>Get Started</button>";
    sPage += "<div class='si_text'>Have an account? ";
    sPage += "<a href=\"javascript:LoginFrame()\" class='si_link'>Log in</a>";
    sPage += "</div>";
    sPage += "</div>";
    sPage += "</div>";
    document.getElementById('Main').innerHTML = sPage;
}

function LoginFrame() {
    let sPage = "";
    sPage += "<div class='si' style='height: 338px;'>";
    sPage += "<div class='si_text si_header'>Log in</div>";
    sPage += "<div id='feedback' class='si_text si_subHead'>to continue to site</div>";
    sPage += "<div class='si_innerContainer'>";
    sPage += "<input id='username' type='input' class='si_textBox' placeholder='Username' maxlength=15 title='username' />";
    sPage += "<input id='password' type='password' class='si_textBox' placeholder='Password' title='password' />";
    sPage += "<div id='Memory' class='si_text si_subHead si_checkbox' onClick='toggleMemory()' title='green remembers you'>Remember Me</div>";
    sPage += "<button class='si_textBox si_button' onClick='checkLogin()'>Log in</button>";
    sPage += "<div class='si_text'>Don't have an account? ";
    sPage += "<a href=\"javascript:SignUpFrame()\" class='si_link'>Sign up</a>";
    sPage += "</div>";
    sPage += "</div>";
    sPage += "</div>";
    document.getElementById('Main').innerHTML = sPage;
}

function toggleMemory() {
    let bOff = document.getElementById('Memory').style.color === "rgb(185, 9, 11)";
    document.getElementById('Memory').style.color = bOff ? "#A4C639" : "#B9090B";
}

function createAccount() {
    const sUsername = document.getElementById('username').value;
    const sPassword = document.getElementById('password').value;
    const sConfirm = document.getElementById('confirm').value;

    if (!sUsername || !sPassword || !sConfirm) {
        document.getElementById('feedback').style.color = "rgb(185, 9, 11)";
        document.getElementById('feedback').innerHTML = "please fill out all fields";
        return;
    }
    if (sPassword !== sConfirm) {
        document.getElementById('feedback').style.color = "rgb(185, 9, 11)";
        document.getElementById('feedback').innerHTML = "password and confirm don't match";
        return;
    }

    // qt check username avail
    // make account
    // check cookies with let bOff = document.getElementById('Memory').style.color === "rgb(185, 9, 11)";
    document.getElementById('feedback').style.color = "#A4C639";
    document.getElementById('feedback').innerHTML = "account created"; // maybe toast this
}

function checkLogin() {
    const sUsername = document.getElementById('username').value;
    const sPassword = document.getElementById('password').value;

    if (!sUsername || !sPassword) {
        document.getElementById('feedback').style.color = "rgb(185, 9, 11)";
        document.getElementById('feedback').innerHTML = "please fill out all fields";
        return;
    }

    // check login credentials
    // check cookies
}


var HashThis = (sText, nRounds) => { // sha3_256 function
    alert();
    for (let x = 0; x < nRounds; x++) {
        sText = sha3_256(sText);
        if (sText == "XisaWmD3iyJ2q1YaZNcCRD7hlDxZKpFp92l6YM7m8Y8=") {
            alert(nRounds);
            return;
        }
    }
    alert(sText);
}

