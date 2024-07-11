import { Button, Flex, FormControl, FormLabel, Input } from "@chakra-ui/react";
import { HeatingPeriod } from "../../hooks/useSettings";

export const Period = ({
  period: { start, end, temperature, index },
  onChange,
  onDelete,
}: {
  period: HeatingPeriod & { index: number };
  onChange: (
    index: number,
    start: string,
    end: string,
    temperature: number
  ) => void;
  onDelete: (index: number) => void;
}) => {
  return (
    <Flex alignItems="flex-end" gap={1} grow={1} dir="row">
      <FormControl>
        <FormLabel>Początek</FormLabel>
        <Input
          onChange={(e) => onChange(index, e.target.value, end, temperature)}
          value={start}
          type="time"
        />
      </FormControl>
      <FormControl>
        <FormLabel>Koniec</FormLabel>
        <Input
          onChange={(e) => onChange(index, start, e.target.value, temperature)}
          value={end}
          type="time"
        />
      </FormControl>
      <FormControl>
        <FormLabel>Temperatura</FormLabel>
        <Input
          onChange={(e) =>
            onChange(index, start, end, parseFloat(e.target.value))
          }
          value={temperature}
          type="number"
        />
      </FormControl>
      <Button onClick={() => onDelete(index)}>-</Button>
    </Flex>
  );
};
