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
            <h1 style="text-decoration: underline;">Create a New Item</h1>
            <form action="../add_php_scripts/items.php" method="post">
                <input type="text" name="item_name" placeholder="Item Name" required>
                <select name="c_name">
                    <option value="none" selected disabled>Choose a Category</option>
                    <?php
                    $sql = "SELECT c_name FROM categories;";
                    $result = mysqli_query($conn, $sql);
                    while ($row = $result->fetch_assoc()) {
                    ?>
                        <option><?php echo $row["c_name"]; ?></option>
                    <?php
                    }
                    ?>
                </select>
                <input type="number" name="quantity" placeholder="Quantity" required>
                <label for="cons" style="margin-left: 285px;">Is Consumable?</label>
                <label><input type="radio" name="consumable" id="cons" value="Yes" required>Yes</label>
                <label><input type="radio" name="consumable" id="cons" value="No">No</label>
                <input type="submit" style="margin-bottom: 10px;" name="submit" value="Add">
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