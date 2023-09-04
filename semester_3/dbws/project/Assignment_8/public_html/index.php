<?php
session_start();

if (isset($_SESSION["loggedin"]) && $_SESSION["loggedin"] === true) {
    header("location: home.php");
    exit;
}
include "./connection.php";
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $err = NULL;
    $email = $_POST["email"];
    $pass = $_POST["password"];
    $sql = "SELECT full_name FROM person WHERE email='$email'";
    $result = mysqli_query($conn, $sql);
    $fname = $result->fetch_assoc()["full_name"];
    $sql = "SELECT id FROM person WHERE email='$email'";
    $result = mysqli_query($conn, $sql);
    if ($result->num_rows == 0) {
        // echo "Incorrect email";
        $err = true;
    } else {
        $id = $result->fetch_assoc()["id"];
        $sql = "SELECT pass_word FROM admins WHERE id=$id";
        $result = mysqli_query($conn, $sql);
        $ret_pass = $result->fetch_assoc()["pass_word"];
        if ($ret_pass == $pass) {
            session_start();
            $_SESSION["loggedin"] = true;
            $_SESSION["id"] = $id;
            $_SESSION["name"] = $fname;
            header("location: home.php");
        } else {
            // echo "Incorrect Password";
            $err = true;
        }
    }
}


?>

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

    <div class="page">
        <?php if ($err) {
            echo "<script type='text/javascript'>alert('Incorrect Email or Password');</script>";
        }
        ?>
        <h1 class="home">Welcome to the Product Management System</h1>
        <?php if ($_SESSION["loggedin"]) { ?>
            <h1 class="home">You are logged in as <?php echo $_SESSION["name"]; ?></h1>
        <?php
        } else {
            echo "<h1 class='home'>Please login to make/handle/view requests</h1>";
        } ?>

        <form action="<?php echo $_SERVER['PHP_SELF']; ?>" id="login" method="post">
            <div class="form">
                <!-- <label for="email">Email Address</label> -->
                <input type="text" name="email" placeholder="xyz@company.de" required>

                <!-- <label for="password">Password</label> -->
                <input type="password" name="password" placeholder="password" required>
                <input type="submit" name="login" placeholder="Login">
            </div>
        </form>
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