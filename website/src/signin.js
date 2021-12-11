var g_sNoCookiesKey = "";

var onload = function() {
    let UN = getCookie('UN');
    let PW = getCookie('PW');
    if (UN && PW) {
        Login(UN, PW);
        return;
    }
    SignUpFrame();
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
    sPage += "<div id='Toast' class='Toast'></div>";
    document.getElementById('Main').innerHTML = sPage;
}

function MainFrame() {
    let sPage = "";
    sPage += "<div id='Toast' class='Toast'></div>";
    document.getElementById('Main').innerHTML = sPage;
}

function toggleMemory() {
    let bOff = document.getElementById('Memory').style.color === "rgb(185, 9, 11)";
    document.getElementById('Memory').style.color = bOff ? "#A4C639" : "#B9090B";
}

function createAccount() {
    let sUsername = document.getElementById('username').value.trim();
    let sPassword = document.getElementById('password').value.trim();
    let sConfirm = document.getElementById('confirm').value.trim();

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

    sUsername = HashThis(sUsername, 10000);

    postFileFromServer("srv/signin.php", "uniqueUN=" + encodeURIComponent(sUsername), uniqueUNCallback);
    function uniqueUNCallback(data) {
        if (data) {
            document.getElementById('feedback').style.color = "rgb(185, 9, 11)";
            document.getElementById('feedback').innerHTML = "username taken, sorry";
            return;
        }
    }

    sPassword = HashThis(sPassword, 10000);

    if (document.getElementById('Memory').style.color !== "rgb(185, 9, 11)") {
        setCookie('UN', sUsername, 999);
        setCookie('PW', sPassword, 999);
    }
    else
        g_sNoCookiesKey = HashThis(sPassword, 10000);

    let objUserData = {};
    objUserData.username = sUsername;
    objUserData.password = HashThis(sPassword, 20000);
    let jsonUserData = JSON.stringify(objUserData);
    postFileFromServer("srv/signin.php", "createAccount=" + encodeURIComponent(jsonUserData), createAccountCallback);
    function createAccountCallback(data) {
        if (data) {
            MainFrame();
            Toast("Account Created");
        }
    }
}

function checkLogin() {
    let sUsername = document.getElementById('username').value;
    let sPassword = document.getElementById('password').value;
    if (!sUsername || !sPassword) {
        document.getElementById('feedback').style.color = "rgb(185, 9, 11)";
        document.getElementById('feedback').innerHTML = "please fill out all fields";
        return;
    }
    sUsername = HashThis(sUsername, 10000);
    sPassword = HashThis(sPassword, 10000);
    if (document.getElementById('Memory').style.color !== "rgb(185, 9, 11)") {
        setCookie('UN', sUsername, 999);
        setCookie('PW', sPassword, 999);
    }
    else
        g_sNoCookiesKey = sPassword;

    Login(sUsername, sPassword);
}

function Login(UN, PW) {
    PW = HashThis(PW, 20000);

    let objCredentials = {};
    objCredentials.un = UN;
    objCredentials.pw = PW;
    let jsonCredentials = JSON.stringify (objCredentials);

    postFileFromServer("srv/signin.php", "login=" + encodeURIComponent(jsonCredentials), LogInCallback);
    function LogInCallback(data) {
        if (data)
            MainFrame();
        else
            Toast("Login failed");
    }
}


