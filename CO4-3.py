# IPSec Security Association Manager

security_associations = {}


def create_sa():
    print("\n--- Create Security Association ---")

    sa_id = input("Enter SA ID: ")

    if sa_id in security_associations:
        print("SA already exists!")
        return

    source = input("Enter Source IP: ")
    destination = input("Enter Destination IP: ")
    protocol = input("Enter Protocol (AH/ESP): ")
    encryption = input("Enter Encryption Algorithm: ")
    authentication = input("Enter Authentication Algorithm: ")
    spi = input("Enter SPI: ")
    key = input("Enter Key: ")

    security_associations[sa_id] = {
        "Source IP": source,
        "Destination IP": destination,
        "Protocol": protocol,
        "Encryption": encryption,
        "Authentication": authentication,
        "SPI": spi,
        "Key": key
    }

    print("Security Association created successfully!")


def lookup_sa():
    print("\n--- Lookup Security Association ---")

    sa_id = input("Enter SA ID: ")

    if sa_id not in security_associations:
        print("SA not found!")
        return

    sa = security_associations[sa_id]

    print("\nSA Details")
    print("SA ID          :", sa_id)
    print("Source IP      :", sa["Source IP"])
    print("Destination IP :", sa["Destination IP"])
    print("Protocol       :", sa["Protocol"])
    print("Encryption     :", sa["Encryption"])
    print("Authentication :", sa["Authentication"])
    print("SPI            :", sa["SPI"])
    print("Key            :", sa["Key"])


def delete_sa():
    print("\n--- Delete Security Association ---")

    sa_id = input("Enter SA ID: ")

    if sa_id in security_associations:
        del security_associations[sa_id]
        print("Security Association deleted successfully!")
    else:
        print("SA not found!")


def display_all():
    print("\n--- All Security Associations ---")

    if not security_associations:
        print("No Security Associations available.")
        return

    for sa_id, sa in security_associations.items():
        print("\nSA ID:", sa_id)
        print("Source      :", sa["Source IP"])
        print("Destination :", sa["Destination IP"])
        print("Protocol    :", sa["Protocol"])
        print("SPI         :", sa["SPI"])


while True:

    print("\n===== IPSec SA Manager =====")
    print("1. Create SA")
    print("2. Lookup SA")
    print("3. Delete SA")
    print("4. Display All SAs")
    print("5. Exit")

    choice = input("Enter your choice: ")

    if choice == "1":
        create_sa()

    elif choice == "2":
        lookup_sa()

    elif choice == "3":
        delete_sa()

    elif choice == "4":
        display_all()

    elif choice == "5":
        print("Program terminated.")
        break

    else:
        print("Invalid choice!")
