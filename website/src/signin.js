var onload = function() {
    // check cookies and shit
    SignInFrame();
}

function SignInFrame() {
    let sPage = "";

    sPage += "<div class='si'>";

    sPage += "<div class='si_text si_header'>Sign Up</div>";
    sPage += "<div class='si_text si_subHead'>to continue to site</div>";

    sPage += "<div class='si_innerContainer'>";
    sPage += "<input id='username' type='input' class='si_textBox' placeholder='Username' maxlength=15 title='username' />";
    sPage += "<input id='password' type='input' class='si_textBox' placeholder='Password' title='password' />";
    sPage += "<input id='confirm' type='input' class='si_textBox' placeholder='Confirm Password' title='confirm password' />";
    sPage += "<button class='si_textBox si_button'>Get Started</button>";
    sPage += "</div>";

    sPage += "</div>";

    document.getElementById('Main').innerHTML = sPage;
}
