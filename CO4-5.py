# Simple Email Spam Classifier

spam_words = [
    "free",
    "winner",
    "win",
    "prize",
    "offer",
    "money",
    "lottery",
    "click",
    "urgent",
    "claim",
    "bonus",
    "congratulations",
    "discount"
]


def classify_email(sender, subject, body):

    score = 0
    reasons = []

    text = (sender + " " + subject + " " + body).lower()

    # Check suspicious sender
    if "noreply" in sender.lower():
        score += 1
        reasons.append("Suspicious sender")

    if "unknown" in sender.lower():
        score += 2
        reasons.append("Unknown sender")

    # Check spam words
    for word in spam_words:

        if word in text:
            score += 1
            reasons.append("Spam keyword: " + word)

    # Check subject
    if "urgent" in subject.lower():
        score += 2
        reasons.append("Urgent subject")

    if "free" in subject.lower():
        score += 2
        reasons.append("Promotional subject")

    # Final decision
    if score >= 4:
        result = "SPAM"
    else:
        result = "LEGITIMATE"

    return result, score, reasons


print("===== Email Spam Classifier =====")

sender = input("Enter sender email: ")
subject = input("Enter subject: ")
body = input("Enter email body: ")

result, score, reasons = classify_email(
    sender,
    subject,
    body
)

print("\n----- Result -----")
print("Spam Score:", score)
print("Classification:", result)

if reasons:
    print("\nReasons:")
    for reason in reasons:
        print("-", reason)
