import { Container, Heading, SimpleGrid, Text } from "@chakra-ui/react";
import { useData } from "../hooks/useData";

export const Home = () => {
  const { data, isSuccess } = useData();

  return (
    <Container>
      <Heading>Dom</Heading>
      {isSuccess &&
        (() => {
          const { temperature, targetTemperature, time, heating } = data;
          return (
            <SimpleGrid columns={2}>
              <Text>Godzina:</Text>
              <Text>{time}</Text>

              <Text>Temperatura: </Text>
              <Text color={temperature > targetTemperature ? "green" : "red"}>
                {temperature}°C
              </Text>
              <Text>Docelowa:</Text>
              <Text>{targetTemperature}°C</Text>
              <Text>Grzałka:</Text>
              <Text color={heating ? "green" : "red"}>
                {heating ? "Aktywna" : "Nieaktywna"}
              </Text>
            </SimpleGrid>
          );
        })()}
    </Container>
  );
};
