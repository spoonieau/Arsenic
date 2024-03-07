// Get current sensor readings when the page loads  
window.addEventListener('load', getWifiDetails);
// Function to get current readings on the webpage when it loads for the first time

let unitsSelected;

function warn() 
{
  alert ("Warrning This device is only to be used as a guide only.\n Seek Refrigerant Specifications.");
}

function wifiDetailsUpdate()
{
  var newSsid = document.getElementById("ssid").value;
  newSsid = newSsid.trim();
  console.log("Device new SSID " + newSsid);

  var newPwd = document.getElementById("password").value;
  
  console.log("Device new PWD " + newPwd);

  var newUnits = document.getElementById("units").value;
  console.log("Device units set to " + newUnits);

  if ( newPwd.length < 9)
  {
    alert ("Password needs to be a minium of nine characters");
    console.log("Password needs to be a minium of nine characters")
    return;
  }
  else if (newSsid.length < 1)
  {
    alert("Hostname/SSID can not be empty")
    console.log("Hostname/SSID can not be empty");
    return;
  }
  else
  {
    alert ("Device will need to restart for changes to take effect.\nPlease allow 10 secons for device load and\nreconnect with you new credentials.");

    var xhr = new XMLHttpRequest();
    xhr.open('post', '/newWifi');
    xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhr.send('ssid=' + newSsid + '&' + 'pwd=' + newPwd + '&' + 'unit=' + newUnits);

    console.log(newSsid + " " + newPwd + " " + newUnits + " " + "Sent to device");
  }

}

function getWifiDetails()
{
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() 
  {
    if (this.readyState == 4 && this.status == 200) 
    {
      var myObj = JSON.parse(this.responseText);
      console.log(myObj);
      document.getElementById("ssid").value = myObj.ssid;
      document.getElementById("password").value = myObj.pwd;
      document.getElementById("units").value = myObj.unit;
      unitsSelected = myObj.unit;
      
      DocumentFragment.getElementById()
    }
  }; 
  xhr.open("GET", "/wifi", true);
  xhr.send();

  getReadings();
}


function getReadings()
{
  var xhr = new XMLHttpRequest();
  warn();
  xhr.onreadystatechange = function() 
  {
    if (this.readyState == 4 && this.status == 200) 
    {
      var myObj = JSON.parse(this.responseText);
      console.log(myObj);
      
      if (unitsSelected == 0)
      {
        var vTemp = (String (myObj.ventTemp) + "&deg;C");
        var aTemp = (String (myObj.atmosTemp) + "&deg;C");
        var aPress = (String (((myObj.atmosPress) * 0.001).toFixed(2)) + "Kpa");
        var r134aPress = (String (myObj.r134aKpa) + "Kpa");
        var r1234yfPress = (String (myObj.r1234yfKpa) + "Kpa");
        var r744Press = (String (myObj.r744Kpa) + "Kpa");
        var hychill30Press = (String (myObj.hychill30) + "Kpa");
              
        document.getElementById("venttemp").innerHTML = vTemp;
        document.getElementById("atmostemp").innerHTML = aTemp;
        document.getElementById("atmopress").innerHTML = aPress;
        document.getElementById("r134a").innerHTML = r134aPress;
        document.getElementById("r1234yf").innerHTML = r1234yfPress;
        document.getElementById("r744").innerHTML = r744Press;
        document.getElementById("hc30").innerHTML = hychill30Press;
      }

      if (unitsSelected == 1)
      {
        let vTempF = myObj.ventTemp;
        var vTemp = (String ((Math.round(vTempF * 1.8)+ 32)) + "&deg;F");
        
        let aTempF = myObj.atmosTemp;
        var aTemp = (String ((Math.round(aTempF * 1.8)+ 32)) + "&deg;F");
        
        let aPressP = myObj.atmosPress;
        var aPress = (String ((aPressP * 0.1450377377).toFixed(2)) + " Psi");

        let r134aPressP = myObj.r134aKpa;
        var r134aPress = (String ((r134aPressP * 0.1450377377).toFixed(2)) + " Psi");
        
        let r1234yfPressP = myObj.r1234yfKpa;
        var r1234yfPress = (String ((r1234yfPressP * 0.1450377377).toFixed(2)) + " Psi");

        let r744PressP = myObj.r744Kpa;
        var r744Press  = (String ((r744PressP * 0.1450377377).toFixed(2)) + " Psi");

        let hychill30PressP = myObj.hychill30;
        var hychill30Press  = (String ((hychill30PressP * 0.1450377377).toFixed(2)) + " Psi");
                
        document.getElementById("venttemp").innerHTML = vTemp;
        document.getElementById("atmostemp").innerHTML = aTemp;
        document.getElementById("atmopress").innerHTML = aPress;
        document.getElementById("r134a").innerHTML = r134aPress ;
        document.getElementById("r1234yf").innerHTML = r1234yfPress;
        document.getElementById("r744").innerHTML = r744Press;
        document.getElementById("hc30").innerHTML = hychill30Press;
      }
      var aHum = (String (myObj.atmosHum));
      document.getElementById("atmoshum").innerHTML = aHum;

      let bSoc = myObj.battSoc;
      var bSocN
      if (bSoc > 100)
      {
        bSocN = String(100 + "%");
      }
      else
      {
        bSocN = String(bSoc + "%");
      }
      document.getElementById("bsoc").innerHTML = bSocN;
    }
  }; 
  xhr.open("GET", "/readings", true);
  xhr.send();
}

if (!!window.EventSource) 
{
  var source = new EventSource('/events');
  
  source.addEventListener('open', function(e) 
  {
    console.log("Events Connected");
  }, false);

  source.addEventListener('error', function(e) 
  {
    if (e.target.readyState != EventSource.OPEN) 
    {
      console.log("Events Disconnected");
    }
  }, false);
  
  source.addEventListener('message', function(e) 
  {
    console.log("message", e.data);
  }, false);
  
  source.addEventListener('new_readings', function(e) 
  {
    console.log("new_readings", e.data);
    var myObj = JSON.parse(e.data);
    console.log(myObj);
    
    if (unitsSelected == 0)
      {
        var vTemp = (String (myObj.ventTemp) + "&deg;C");
        var aTemp = (String (myObj.atmosTemp) + "&deg;C");
        var aPress = (String (((myObj.atmosPress) * 0.001).toFixed(2)) + "Kpa");
        var r134aPress = (String (myObj.r134aKpa) + "Kpa");
        var r1234yfPress = (String (myObj.r1234yfKpa) + "Kpa");
        var r744Press = (String (myObj.r744Kpa) + "Kpa");
        var hychill30Press = (String (myObj.hychill30) + "Kpa");
              
        document.getElementById("venttemp").innerHTML = vTemp;
        document.getElementById("atmostemp").innerHTML = aTemp;
        document.getElementById("atmopress").innerHTML = aPress;
        document.getElementById("r134a").innerHTML = r134aPress;
        document.getElementById("r1234yf").innerHTML = r1234yfPress;
        document.getElementById("r744").innerHTML = r744Press;
        document.getElementById("hc30").innerHTML = hychill30Press;
      }

      if (unitsSelected == 1)
      {
        let vTempF = myObj.ventTemp;
        var vTemp = (String ((Math.round(vTempF * 1.8)+ 32)) + "&deg;F");
        
        let aTempF = myObj.atmosTemp;
        var aTemp = (String ((Math.round(aTempF * 1.8)+ 32)) + "&deg;F");
        
        let aPressP = myObj.atmosPress;
        var aPress = (String ((aPressP * 0.1450377377).toFixed(2)) + " Psi");

        let r134aPressP = myObj.r134aKpa;
        var r134aPress = (String ((r134aPressP * 0.1450377377).toFixed(2)) + " Psi");
        
        let r1234yfPressP = myObj.r1234yfKpa;
        var r1234yfPress = (String ((r1234yfPressP * 0.1450377377).toFixed(2)) + " Psi");

        let r744PressP = myObj.r744Kpa;
        var r744Press  = (String ((r744PressP * 0.1450377377).toFixed(2)) + " Psi");

        let hychill30PressP = myObj.hychill30;
        var hychill30Press  = (String ((hychill30PressP * 0.1450377377).toFixed(2)) + " Psi");
                
        document.getElementById("venttemp").innerHTML = vTemp;
        document.getElementById("atmostemp").innerHTML = aTemp;
        document.getElementById("atmopress").innerHTML = aPress;
        document.getElementById("r134a").innerHTML = r134aPress ;
        document.getElementById("r1234yf").innerHTML = r1234yfPress;
        document.getElementById("r744").innerHTML = r744Press;
        document.getElementById("hc30").innerHTML = hychill30Press;
      }
      var aHum = (String (myObj.atmosHum));
      document.getElementById("atmoshum").innerHTML = aHum;

      let bSoc = myObj.battSoc;
      let bSocN
      if (bSoc > 100)
      {
        bSocN = String(100 + "%");
      }
      else
      {
        bSocN = String(bSoc + "%");
      }
      document.getElementById("bsoc").innerHTML = bSocN;      
  }, false);
}