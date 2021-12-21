<?php

if (isset($_POST['addContact']))
    $jsonPostData = $_POST['addContact'];

if ($jsonPostData)
    $sFeedback = addContact ($jsonPostData);

echo $sFeedback;


function addContact ($jsonPostData) {
    $objPostData = json_decode($jsonPostData);
    $sSQL = "INSERT INTO Contacts (user, data) VALUES (" . $objPostData->id . " , '" . $objPostData->data . "')";
    QueryDB($sSQL);
    return $objPostData->data;
}

function QueryDB ($sSQL) {
    $dbhost = 'localhost';
    $dbuser = 'jake_contacts';
    $dbpass = 'Yv9zEtKfr5yMPgkvWa4v9N';
    $db = "Contacts";
    $dbconnect = new mysqli($dbhost, $dbuser, $dbpass, $db);
    $Result = $dbconnect->query($sSQL);
    $dbconnect->close();
    return $Result;
}

?>
