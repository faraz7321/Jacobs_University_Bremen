<!DOCTYPE html>
<html lang="en">

<head>
    <meta name="viewport" content="width=device-width" , initial-scale="1.0">
    <title>PMS</title>
    <link rel="icon" href="../images/favicon.png">
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
        <a href="auto_complete.php">Auto Complete</a>
        <!-- <a href="contact.html">Contact</a> -->
    </div>

    <div class="page">
        <h1 class="home">Welcome to the Product Management System</h1>
        <!-- <h1 class="home">Please login to make/handle/view requests</h1> -->
        <?php if ($_SESSION["loggedin"]) { ?>
            <h1 class="home">Hello <?php echo $_SESSION["name"]; ?>. You are logged in as an Admin</h1>
        <?php } else {?>
        <h1 class='home'>Please login to make/handle/view requests</h1>
        <form action="index.php" id="login" method="post">
            <div class="form">
                <!-- <label for="email">Email Address</label> -->
                <input type="text" name="email" placeholder="xyz@company.de" required>

                <!-- <label for="password">Password</label> -->
                <input type="password" name="password" placeholder="password" required>
                <input type="submit" name="login" placeholder="Login">
            </div>
        </form>
        <?php } ?>

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

</body>

</html>