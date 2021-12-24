function MainFrame() {
    document.getElementById('Body').style.backgroundColor = "#282828";

    let sPage = "";

    sPage += "<div class='m_head'>";
    sPage += "<div class='m_headImgContainer m_menu'>";
    sPage += "<img src='images/menu64.png' class='m_headerImg' title='Menu...'>";
    sPage += "</div>";
    sPage += "<div class='m_searchContainer'>";
    sPage += "<input type='input' id='search' class='m_headSearch' placeholder='Search' />"; // add Contacts (headre)
    sPage += "</div>";
    sPage += "<div class='m_changeUserData m_headImgContainer'>";
    sPage += "<img src='images/accountsettings128.png' class='m_headerImg' title='Account Settings'>";
    sPage += "</div>";
    sPage += "</div>";

    sPage += "<div class='RoundedBox m_body'>";
    sPage += "<button onClick='AddFrame()'>Add</button>";
    sPage += "</div>";

    sPage += "<div id='Toast' class='Toast'></div>";
    document.getElementById('Main').innerHTML = sPage;
    document.getElementById('search').addEventListener('keyup', Search);
    // pullUserData();
}

const pullUserData = () => {
    alert();
}

function Search() {
    // ajax db
}

function AddFrame() {
    let sPage = "";
    sPage += "<div class='RoundedBox m_body'>";

    sPage += "<input type='input' id='first' placeholder='First'  />";
    sPage += "<input type='input' id='middle' placeholder='Middle'  />";
    sPage += "<input type='input' id='last' placeholder='Last'  />";
    sPage += "<input type='input' id='company' placeholder='Company'  />";
    sPage += "<input type='input' id='title' placeholder='Title'  />";
    sPage += "<input type='input' id='home' placeholder='Home'  />";
    sPage += "<input type='input' id='mobile' placeholder='Mobile'  />";
    sPage += "<input type='input' id='work' placeholder='Work'  />";
    sPage += "<input type='input' id='address' placeholder='Address'  />";
    sPage += "<input type='input' id='email' placeholder='Email'  />";
    sPage += "<input type='input' id='website' placeholder='Website'  />";
    sPage += "<input type='input' id='state' placeholder='State'  />";
    sPage += "<input type='input' id='city' placeholder='City'  />";
    sPage += "<input type='input' id='zip' placeholder='Zip'  />";
    sPage += "<input type='input' id='birthday' placeholder='Birthday'  />";
    sPage += "<input type='input' id='anniversary' placeholder='Anniversary'  />";
    sPage += "<input type='input' id='notes' placeholder='Notes'  /><br><br>";

    sPage += "<button id='confirm' onClick='addContact()'>Add</button>";
    sPage += "<button id='confirm' onClick='MainFrame()'>Back</button>";
    sPage += "</div>";

    sPage += "<div id='Toast' class='Toast'></div>";
    document.getElementById('Main').innerHTML = sPage;
}

function addContact() {
    const sFirst = document.getElementById('first').value;
    const sCompany = document.getElementById('company').value;
    if ("" === sFirst && "" === sCompany) {
        Toast("either first or company must be filled out");
        return;
    }

    let objContactData = {};
    objContactData.address = document.getElementById('address').value;
    objContactData.anniversary = document.getElementById('anniversary').value;
    objContactData.birthday = document.getElementById('birthday').value;
    objContactData.city = document.getElementById('city').value;
    objContactData.company = sCompany;
    objContactData.email = document.getElementById('email').value;
    objContactData.first = sFirst;
    objContactData.home = document.getElementById('home').value;
    objContactData.last = document.getElementById('last').value;
    objContactData.middle = document.getElementById('middle').value;
    objContactData.mobile = document.getElementById('mobile').value;
    objContactData.notes = document.getElementById('notes').value;
    objContactData.state = document.getElementById('state').value;
    objContactData.title = document.getElementById('title').value;
    objContactData.website = document.getElementById('website').value;
    objContactData.work = document.getElementById('work').value;
    objContactData.zip = document.getElementById('zip').value;

    let jsonContactData = JSON.stringify(objContactData);

    let sKey = g_objUserData.password.substring(0, 32);
    let sIV = g_objUserData.password.substring(32);

    jsonContactData = CryptoJS.AES.encrypt(jsonContactData, sKey, {iv: sIV});

    let objPostData = {};
    objPostData.id = g_objUserData.id;
    objPostData.data = jsonContactData;

    alert(objPostData.data);

    let text = AESDecrypt(objPostData.data);
    alert(text);

    return;

    let jsonPostData = JSON.stringify(objPostData);

    postFileFromServer("srv/main.php", "addContact=" + encodeURIComponent(jsonPostData), addContactCallback);
    function addContactCallback(data) {
        if (data) {
            alert(AESDecrypt(data));
            MainFrame();
        }
        else
            alert("nun here");
    }
}

CryptoJS.pad.NoPadding={pad:function(){},unpad:function(){}};
CryptoJS.pad.ZeroPadding={pad:function(a,c){var b=4*c;a.clamp();a.sigBytes+=b-(a.sigBytes%b||b)},unpad:function(a){for(var c=a.words,b=a.sigBytes-1;!(c[b>>>2]>>>24-8*(b%4)&255);)b--;a.sigBytes=b+1}};

CryptoJS.mode.ECB=function(){var a=CryptoJS.lib.BlockCipherMode.extend();a.Encryptor=a.extend({processBlock:function(a,b){this._cipher.encryptBlock(a,b)}});a.Decryptor=a.extend({processBlock:function(a,b){this._cipher.decryptBlock(a,b)}});return a}();


