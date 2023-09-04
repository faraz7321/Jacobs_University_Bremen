<!DOCTYPE html>
<html lang="en">

<head>
    <meta name="viewport" content="width=device-width" , initial-scale="1.0">
    <title>PMS</title>
    <link rel="icon" href="images/favicon.png">
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <div class="topbar">
        <a href="../about.php">About</a>
        <a href="../imprint.php">Imprint</a>
        <?php
        session_start();
        if ($_SESSION["loggedin"]) { ?>
            <a href="../logout.php">Logout</a>
        <?php } ?>
    </div>

    <div class="sidebar">
        <a href="../home.php">
            <img src="../images/favicon.png" alt="logo">
        </a>
        <a href="../home.php" id="current">Home</a>
        <a href="../inventory.php">Inventory</a>
        <?php if ($_SESSION["loggedin"]) { ?>
            <a href="../maintenance.php">Maintenance</a>
        <?php } ?>
        <a href="../search.php">Search</a>
        <!-- <a href="contact.html">Contact</a> -->
    </div>
    <div class="page">
        <h1 style="text-align:center; color:burlywood; padding-left:600px;text-decoration: underline; position:absolute; top:30%;">
            The Record was added successfully
        </h1>
        <a href="../maintenance.php" style="text-align:center; padding-left:605px; position:absolute; top:40%;">Back to Maintenance</a>
        <p id="imprint">
            This website is student lab work and does not necessarily reflect Jacobs University Bremen opinions. Jacobs University Bremen does not endorse this site, nor is it checked by Jacobs University
            Bremen regularly, nor is it part of the official Jacobs University Bremen web presence.
            For each external link existing on this website, we initially have checked that the target page
            does not contain contents which is illegal wrt. German jurisdiction. However, as we have no influence on such contents, this may change without our notice. Therefore we deny any responsibility for the websites referenced through our external links from here.
            No information conflicting with GDPR is stored in the server.
        </p>
    </div>
</body>

</html>