<!DOCTYPE html>
<html lang="en">

<head>
    <meta name="viewport" content="width=device-width" , initial-scale="1.0">
    <title>PMS</title>
    <link rel="icon" href="images/favicon.png">
    <link rel="stylesheet" href="css/style.css">
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
        <a href="home.php" id="current">Home</a>
        <a href="inventory.php">Inventory</a>
        <?php if ($_SESSION["loggedin"]) { ?>
            <a href="maintenance.php">Maintenance</a>
        <?php } ?>
        <a href="search.php">Search</a>
        <!-- <a href="contact.html">Contact</a> -->
    </div>
    </div>
    <div class="page">
        <h1 class="about">Group 30</h1>
        <h2 class="about">Product Management System</h2>
        <h4 class="about">By Muaaz Rajput & Faraz Ahmad</h4>
        <p class="intro">
            This website serves as the project for the Databases and Web Services course,
            taught in the 3rd semester by Prof Peter Baumann. The website represents a Product
            Management System which can be implemented within an office environment. The System
            consists of employees who can make requests to borrow some office equipment, and admins
            that can view and handle these requests. This frontend is to be connected with a
            database storing information about all employees, including admins, and information about
            all the available products that can be borrowed.
        </p>
        <h4 class="about">Contact us:</h2>
            <ul style="margin-left: 200px;">
                <li>Muaaz Rajput, +49 xxx xxxxxxx, murajput@jacobs-university.de</li>
                <li style="margin-top: 5px;">Faraz Ahmad, +49 xxx xxxxxxx, fa.ahmad@jacobs-university.de</li>
            </ul>
    </div>
    <p id="imprint">
        This website is student lab work and does not necessarily reflect Jacobs University Bremen opinions. Jacobs University Bremen does not endorse this site, nor is it checked by Jacobs University
        Bremen regularly, nor is it part of the official Jacobs University Bremen web presence.
        For each external link existing on this website, we initially have checked that the target page
        does not contain contents which is illegal wrt. German jurisdiction. However, as we have no influence on such contents, this may change without our notice. Therefore we deny any responsibility for the websites referenced through our external links from here.
        No information conflicting with GDPR is stored in the server.
    </p>
</body>

</html>