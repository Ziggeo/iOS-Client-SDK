import React from 'react';
import { StyleSheet, Text, View, Button } from 'react-native';
import { NativeEventEmitter, NativeModules } from 'react-native';

export default class App extends React.Component {
    async record() {
        var recorder = NativeModules.ZiggeoRecorder;
        recorder.setAppToken("ZIGGEO_APPLICATION_ID");
        recorder.setCameraFlipButtonVisible(true);
        recorder.setCoverSelectorEnabled(false);
        recorder.setCamera(recorder.rearCamera);
        const recorderEmitter = new NativeEventEmitter(NativeModules.ZiggeoRecorder);
        const subscription = recorderEmitter.addListener('UploadProgress',(progress)=>console.log("uploaded " + progress.bytesSent + " from " + progress.totalBytes + " total bytes"));
        try
        {
            //record and upload the video and return its token
            var token = await recorder.record();
            alert(token);
        }
        catch(e)
        {
            //recorder error or recording was cancelled by user
            alert(e);
        }
    }
    
    
    render() {
        return (
          <View style={styles.container}>
            <Button
            onPress={this.record}
            title="Record"
            accessibilityLabel="Record"
            />
          </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});
