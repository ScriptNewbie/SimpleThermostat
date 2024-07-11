import { Button, Container, Flex } from "@chakra-ui/react";
import { Home } from "./pages/Home";
import { Settings } from "./pages/Settings";
import { useState } from "react";

function App() {
  const [settings, setSettings] = useState(false);
  return (
    <Container>
      <Flex direction="column" gap={1}>
        <Button alignSelf="flex-end" mt={1} w="fit-content" onClick={() => setSettings(!settings)}>
          {settings ? "Dom" : "Ustawienia"}
        </Button>
        {settings ? <Settings /> : <Home />}
      </Flex>
    </Container>
  );
}

export default App;
