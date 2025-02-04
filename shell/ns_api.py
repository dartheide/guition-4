
import requests
from datetime import datetime

# Replace with your actual API key
API_KEY = "ee64ed40cfe841399dc580c89192bca1"
URL = "https://gateway.apiportal.ns.nl/reisinformatie-api/api/v2/departures?station=hd"

# Format the actualDateTime to a more readable format
def format_time(iso_time):
    try:
        dt = datetime.fromisoformat(iso_time)
        return dt.strftime("%H:%M")
    except (ValueError, TypeError):
        return "Unknown"

# Replace "True"/"False" with "Yes"/"No"
def format_cancelled(cancelled):
    return "NEE" if cancelled else "ja"


# Set up the headers with the API key
headers = {
    "Ocp-Apim-Subscription-Key": API_KEY
}

# Make the API request
response = requests.get(URL, headers=headers)

# Check if the request was successful
if response.status_code == 200:
    # Parse the JSON response
    data = response.json()

    # Extract the first two departures
    departures = data.get("payload", {}).get("departures", [])[:5]

    # Print the origin and actualDateTime for the first four departure
    for i, departure in enumerate(departures, start=1):
        origin = departure.get("direction", "Unknown")
        actual_time = format_time(departure.get("actualDateTime"))
        cancelled = format_cancelled(departure.get("cancelled", False))
        print(f"{origin}, vertrek: {actual_time}, rijdt {cancelled}")
else:
    print(f"Failed to fetch data. Status code: {response.status_code}")
    print(f"Response: {response.text}")
