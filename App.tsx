import React, { useEffect } from "react";
import { Card, Carousel, Col, Row, Typography } from "antd";
import "./App.css";

const { Text } = Typography;

const App: React.FC = () => {
  const responsiveCarousel = () => {
    if (window.innerWidth >= 3840) {
      return 800;
    } else if (window.innerWidth >= 2560) {
      return 600;
    } else if (window.innerWidth >= 1920) {
      return 500;
    } else {
      return 300;
    }
  };

  const listImages = [
    {
      img: "Not1.jpg",
      link: "https://noticias.uniquindio.edu.co/noticias/publicaciones/4119/ingenieria-electronica-trabaja-para-ser-el-primer-programa-en-lograr-la-acreditacion-internacional-arcu-sur/",
    },
    {
      img: "Not2.jpg",
      link: "https://noticias.uniquindio.edu.co/noticias/publicaciones/4114/ingenieria-electronica-estrena-laboratorio-de-prototipado-con-ultima-tecnologia/",
    },
    {
      img: "Not3.jpg",
      link: "https://noticias.uniquindio.edu.co/noticias/publicaciones/4035/estudiante-de-ingenieria-electronica-rumbo-a-canada/",
    },
    {
      img: "Not4.jpg",
      link: "https://noticias.uniquindio.edu.co/noticias/publicaciones/3933/planea-la-exitosa-herramienta-con-la-que-el-programa-de-ingenieria-electronica-promueve-la-calidad-academica/",
    },
  ];

  const listCards = [
    {
      title: "50",
      text: "Cancelación de semestre",
    },
    {
      title: "50",
      text: "Cancelación de semestre con reembolso",
    },
    {
      title: "50",
      text: "Cancelación de asignaturas",
    },
    {
      title: "50",
      text: "Finalización de semestre",
    },
  ];

  useEffect(() => {
    const video = document.getElementById("video") as HTMLVideoElement;
    video.play();
  }, []);

  return (
    <div className='container-general'>
      <Card bordered={false} className='img-container'>
        <img
          src='src\assets\images\logoU.png'
          width={"100%"}
          height={"100%"}
          alt='logo'
        />
      </Card>

      <div style={{ position: "relative" }}>
        <div className='video-container'>
          <video id='video' width='100%' height='auto' autoPlay loop>
            <source src='src\assets\videos\video.mp4' type='video/mp4' />
            <track
              src='src\assets\videos\captions.vtt'
              kind='captions'
              srcLang='en'
              label='English'
            />
            Your browser does not support the video tag.
          </video>
        </div>
        <div className='container-layout'>
          <Col>
            <Row className='container-row'>
              {listCards.map((card, index) => (
                <Card bordered={false} className='card-items' key={index + 100}>
                  <Text className='text-card text-font-40'>
                    {card.title}
                    <Text className='text-card text-font-12'> días</Text>
                  </Text>

                  <Text className='text-card text-font-14'>{card.text}</Text>
                </Card>
              ))}
            </Row>

            <Carousel
              autoplay
              arrows
              dots={false}
              pauseOnDotsHover
              draggable
              autoplaySpeed={5000}
              className='carousel-container'
              style={{}}>
              {listImages.map((image, index) => (
                <a
                  target='_blank'
                  href={image.link}
                  type='default'
                  key={index + 1}
                  className='button-carousel'>
                  <img
                    src={`src\\assets\\images\\${image.img}`}
                    alt='logo'
                    width={"100%"}
                    height={responsiveCarousel()}
                    style={{ objectFit: "cover" }}
                  />
                </a>
              ))}
            </Carousel>

            <a
              href='https://noticias.uniquindio.edu.co/'
              target='_blank'
              type='primary'
              className='button-newspaper'>
              Ver más noticias
            </a>
          </Col>
        </div>
      </div>
    </div>
  );
};

export default App;
