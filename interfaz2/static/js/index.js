const { createApp, ref } = Vue;
const image = ref('');

const app = createApp({
  setup() {
    const pedirImagen = async () => {
      try {
        const response = await fetch('/pedirImagen', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json'
          },
          body: JSON.stringify({ pedirImagen: true })
        });
        
        const data = await response.json();
        image.value = 'data:image/jpeg;base64,' + data.response;
        
      } catch (error) {
        console.error('Error:', error);
      }
    };
    
    return { pedirImagen, image};
  }
});

app.mount('#app');





