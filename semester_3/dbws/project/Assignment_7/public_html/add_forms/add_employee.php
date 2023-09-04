<?php include "./connection.php"; ?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta name="viewport" content="width=device-width" , initial-scale="1.0">
    <title>PMS</title>
    <link rel="icon" href="../images/favicon.png">
    <link rel="stylesheet" href="../css/style.css">
</head>

<body>
    <div class="topbar">
        <a href="about.html">About</a>
        <a href="imprint.html">Imprint</a>
    </div>
    <div class="sidebar">
        <a href="../index.html">
            <img src="images/favicon.png" alt="logo">
        </a>
        <a href="../index.html">Home</a>
        <a href="../inventory.html">Inventory</a>
        <a href="../maintenance.html" id="current">Maintenance</a>
        <a href="../search.html">Search</a>
        <!-- <a href="contact.html">Contact</a> -->
    </div>
    <div class="page">
        <div class="form">
            <h1 style="text-decoration: underline;">Create a New Employee</h1>
            <form action="../add_php_scripts/employee.php" method="post">
                <input type="text" name="f_name" placeholder="Full Name" required>
                <input type="text" name="email" placeholder="Email Address" required>
                <input type="password" name="password" placeholder="Password" required>
                <select name="d_name">
                    <option value="none" selected disabled>Choose a Department</option>
                    <?php
                        $sql = "SELECT name FROM departments;";
                        $result = mysqli_query($conn, $sql);
                        // echo "saisdhakjsdjaksdnkajs asjcnksdjncvslkadjajdopasjdoasjdasndjasidhajsdopijas ".$sql;
                        while($row = $result->fetch_assoc()){
                    ?>
                    <option><?php echo $row["name"]; ?></option>
                <?php
                        }
                ?>
                </select>
                <input type="date" name="dob" placeholder="D.O.B" required>
                <input type="submit" value="Add" name="submit">
            </form>
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
</body>

</html>