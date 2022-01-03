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

    sPage += "<div id='Toast' class='Toast'></div>";
    document.getElementById('Main').innerHTML = sPage;
    document.getElementById('search').addEventListener('keyup', Search);
}

function Search() {

}
