<!DOCTYPE html>
<html lang="en">

<head>
    <meta name="viewport" content="width=device-width" , initial-scale="1.0">
    <title>PMS</title>
    <link rel="icon" href="images/favicon.png">
    <link rel="stylesheet" href="css/style.css">


    <!-- jQuery library -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>

    <!-- jQuery UI library -->
    <link rel="stylesheet" href="https://ajax.googleapis.com/ajax/libs/jqueryui/1.13.2/themes/smoothness/jquery-ui.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jqueryui/1.13.2/jquery-ui.min.js"></script>


</head>

<body>
    <div class="topbar">
        <a href="about.php">About</a>
        <a href="imprint.php">Imprint</a>
        <?php
        session_start();
        if ($_SESSION["loggedin"]) { ?>
            <a href="logout.php">Logout</a>
        <?php } ?>
    </div>

    <div class="sidebar">
        <a href="home.php">
            <img src="images/favicon.png" alt="logo">
        </a>
        <a href="home.php">Home</a>
        <a href="inventory.php">Inventory</a>
        <?php if ($_SESSION["loggedin"]) { ?>
            <a href="maintenance.php">Maintenance</a>
        <?php } ?>
        <a href="search.php">Search</a>
        <a href="auto_complete.html" id="current">Auto Complete</a>
        <!-- <a href="contact.html">Contact</a> -->
    </div>
    <div class="page">
        <div class="form">
            <form action="#" method="POST"></form>
            <input type="text" id="q" name="q" placeholder="Enter Name of Employee">
            <input type="submit" value="Search" name="submit">
        </div>
        <p id="imprint">
            This website is student lab work and does not necessarily reflect Jacobs University Bremen opinions. Jacobs
            University Bremen does not endorse this site, nor is it checked by Jacobs University
            Bremen regularly, nor is it part of the official Jacobs University Bremen web presence.
            For each external link existing on this website, we initially have checked that the target page
            does not contain contents which is illegal wrt. German jurisdiction. However, as we have no influence on
            such contents, this may change without our notice. Therefore we deny any responsibility for the websites
            referenced through our external links from here.
            No information conflicting with GDPR is stored in the server.
        </p>
    </div>
    <script>
        $(function() {
            $("#q").autocomplete({
                source: "auto.php",
            });
        });
    </script>
</body>


</html>