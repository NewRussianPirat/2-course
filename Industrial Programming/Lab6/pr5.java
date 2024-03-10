import java.io.*;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.util.jar.JarEntry;
import java.util.jar.JarOutputStream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;
import javax.crypto.*;
import javax.xml.stream.*;
import javax.xml.stream.events.StartElement;
import javax.xml.stream.events.XMLEvent;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

public class pr5 {
    public static void main(String[] args) throws IOException, XMLStreamException, ParseException, NoSuchPaddingException, NoSuchAlgorithmException, InvalidKeyException, IllegalBlockSizeException, BadPaddingException {
        int n;
        int m;
        int k = 0;
        ArrayList<ArrayList<Integer>> matr = null;

        //--------- XML Reader ---------

/*        XMLInputFactory xmlInputFactory = XMLInputFactory.newInstance();
        InputStream in = new FileInputStream("input.xml");
        XMLEventReader xmlEventReader = xmlInputFactory.createXMLEventReader(in);
        while (xmlEventReader.hasNext()) {
            XMLEvent xmlEvent = xmlEventReader.nextEvent();
            if (xmlEvent.isStartElement()) {
                StartElement startElement = xmlEvent.asStartElement();
                if (startElement.getName().getLocalPart().equals("CountOfArrays")) {
                    xmlEvent = xmlEventReader.nextEvent();
                    n = Integer.parseInt(xmlEvent.asCharacters().toString());
                    matr = new ArrayList<>();
                    for (int i = 0; i < n; ++i) {
                        matr.add(new ArrayList<>());
                    }
                    continue;
                }
                if (startElement.getName().getLocalPart().equals("SizeOfArrays")) {
                    xmlEvent = xmlEventReader.nextEvent();
                    m = Integer.parseInt(xmlEvent.asCharacters().toString());
                    continue;
                }
                if (startElement.getName().getLocalPart().equals("Array")) {
                    for (int i = 0; i < m; ++i) {
                        xmlEvent = xmlEventReader.nextEvent();
                        xmlEvent = xmlEventReader.nextEvent();
                        xmlEvent = xmlEventReader.nextEvent();
                        if (matr != null) {
                            matr.get(k).add(Integer.parseInt(xmlEvent.asCharacters().toString()));
                        }
                        xmlEvent = xmlEventReader.nextEvent();
                    }
                    ++k;
                }
            }
        }*/

        //------------------------------

        //-------- JSON Reader ---------

        JSONObject jsonObject = (JSONObject) new JSONParser().parse(new FileReader("input.json"));
        n = (int) (long) jsonObject.get("count_of_arrays");
        matr = new ArrayList<>();
        for (int i = 0; i < n; ++i) {
            matr.add(new ArrayList<>());
        }
        m = (int) (long) jsonObject.get("size_of_arrays");
        JSONArray jsonArray = (JSONArray) jsonObject.get("matr");
        for (int i = 0; i < n; ++i) {
            JSONArray jsonArray1 = (JSONArray) jsonArray.get(i);
            for (int j = 0; j < m; ++j) {
                matr.get(k).add((int) (long) jsonArray1.get(j));
            }
            ++k;
        }

        //------------------------------

        TreeMap<Pair, HashSet<Integer>> treeMap = new TreeMap<>();
        if (matr != null) {
            Func(0, 0, matr, treeMap);
        }

        Collection<HashSet<Integer>> collection = treeMap.values();
        Collection<Pair> collection1 = treeMap.keySet();
        Iterator<HashSet<Integer>> iterator_values = collection.iterator();
        Iterator<Pair> iterator_pairs = collection1.iterator();

        XMLOutputFactory xmlOutputFactory = XMLOutputFactory.newInstance();
        OutputStream outputStream = new FileOutputStream("output.xml");
        XMLEventFactory xmlEventFactory = XMLEventFactory.newInstance();
        XMLEventWriter xmlEventWriter = xmlOutputFactory.createXMLEventWriter(outputStream);
        xmlEventWriter.add(xmlEventFactory.createStartDocument());
        xmlEventWriter.add(xmlEventFactory.createStartElement("", "", "matrices"));

        FileWriter out = new FileWriter("output.json");
        JSONArray jsonArray1 = new JSONArray();
        while (iterator_pairs.hasNext()) {
            Pair pair = iterator_pairs.next();
            HashSet<Integer> hashSet = iterator_values.next();
            Iterator<Integer> iterator = hashSet.iterator();

            //-------- XML Writer ----------

            xmlEventWriter.add(xmlEventFactory.createStartElement("", "", "matr"));
            xmlEventWriter.add(xmlEventFactory.createStartElement("", "", "size"));
            xmlEventWriter.add(xmlEventFactory.createStartElement("", "", "i"));
            xmlEventWriter.add(xmlEventFactory.createCharacters(Integer.toString(pair.i)));
            xmlEventWriter.add(xmlEventFactory.createEndElement("", "", "i"));
            xmlEventWriter.add(xmlEventFactory.createStartElement("", "", "j"));
            xmlEventWriter.add(xmlEventFactory.createCharacters(Integer.toString(pair.j)));
            xmlEventWriter.add(xmlEventFactory.createEndElement("", "", "j"));
            xmlEventWriter.add(xmlEventFactory.createEndElement("", "", "size"));
            xmlEventWriter.add(xmlEventFactory.createStartElement("", "", "values"));
            while (iterator.hasNext()) {
                xmlEventWriter.add(xmlEventFactory.createStartElement("", "", "value"));
                xmlEventWriter.add(xmlEventFactory.createCharacters(Integer.toString(iterator.next())));
                xmlEventWriter.add(xmlEventFactory.createEndElement("", "", "value"));
            }
            xmlEventWriter.add(xmlEventFactory.createEndElement("", "", "values"));
            xmlEventWriter.add(xmlEventFactory.createEndElement("", "", "matr"));

            //------------------------------

            //-------- JSON Writer ---------

            JSONObject jsonObject2 = new JSONObject();
            jsonObject2.put("size_of_matr", pair);
            jsonObject2.put("elements", hashSet);
            jsonArray1.add(jsonObject2);

            //------------------------------
        }

        xmlEventWriter.add(xmlEventFactory.createEndElement("", "", "matrices"));
        xmlEventWriter.add(xmlEventFactory.createEndDocument());
        xmlEventWriter.flush();
        xmlEventWriter.close();
        out.write(jsonArray1.toJSONString());
        out.close();

        //------- Zip archiving --------

        ZipOutputStream zipOutputStream = new ZipOutputStream(new FileOutputStream("output.zip"));
        FileInputStream fileInputStream = new FileInputStream("output.json");
        ZipEntry zipEntry = new ZipEntry("output.json");
        zipOutputStream.putNextEntry(zipEntry);
        zipOutputStream.write(fileInputStream.readAllBytes());
        zipOutputStream.closeEntry();
        fileInputStream = new FileInputStream("output.xml");
        zipEntry = new ZipEntry("output.xml");
        zipOutputStream.putNextEntry(zipEntry);
        zipOutputStream.write(fileInputStream.readAllBytes());
        zipOutputStream.closeEntry();
        zipOutputStream.close();

        //------------------------------

        //------- Rar archiving --------

        zipOutputStream = new ZipOutputStream(new FileOutputStream("output.rar"));
        fileInputStream = new FileInputStream("output.json");
        zipEntry = new ZipEntry("output.json");
        zipOutputStream.putNextEntry(zipEntry);
        zipOutputStream.write(fileInputStream.readAllBytes());
        zipOutputStream.closeEntry();
        fileInputStream = new FileInputStream("output.xml");
        zipEntry = new ZipEntry("output.xml");
        zipOutputStream.putNextEntry(zipEntry);
        zipOutputStream.write(fileInputStream.readAllBytes());
        zipOutputStream.closeEntry();
        zipOutputStream.close();

        //------------------------------

        //------- Jar archiving --------

        JarOutputStream jarOutputStream = new JarOutputStream(new FileOutputStream("output.jar"));
        fileInputStream = new FileInputStream("output.json");
        JarEntry jarEntry = new JarEntry("output.json");
        jarOutputStream.putNextEntry(jarEntry);
        jarOutputStream.write(fileInputStream.readAllBytes());
        jarOutputStream.closeEntry();
        fileInputStream = new FileInputStream("output.xml");
        jarEntry = new JarEntry("output.xml");
        jarOutputStream.putNextEntry(jarEntry);
        jarOutputStream.write(fileInputStream.readAllBytes());
        jarOutputStream.closeEntry();
        jarOutputStream.close();

        //------------------------------

        //--------- Encryption ----------

        Cipher cipher_encrypted = Cipher.getInstance("AES");
        KeyGenerator keyGenerator = KeyGenerator.getInstance("AES");
        Key key = keyGenerator.generateKey();
        cipher_encrypted.init(Cipher.ENCRYPT_MODE, key);
        byte[] cipherText = cipher_encrypted.doFinal(new FileInputStream("output.json").readAllBytes());
        FileOutputStream fileOutputStream = new FileOutputStream("output_encrypted.json");
        fileOutputStream.write(cipherText);
        fileOutputStream.close();

        Cipher cipher_deencrypted = Cipher.getInstance("AES");
        cipher_deencrypted.init(Cipher.DECRYPT_MODE, key);
        byte[] cipher_deencrypted_Text = cipher_deencrypted.doFinal(new FileInputStream("output_encrypted.json").readAllBytes());
        fileOutputStream = new FileOutputStream("output_deencrypted.json");
        fileOutputStream.write(cipher_deencrypted_Text);
        fileOutputStream.close();

        //------------------------------
    }

    public static Pair Func(int i, int j, ArrayList<ArrayList<Integer>> matr, TreeMap<Pair, HashSet<Integer>> treeMap) {
        Pair j_state;
        Pair i_state;

        if (j + 1 < matr.get(i).size()) {
            Pair pair = Func(i, j + 1, matr, treeMap);
            if (matr.get(i).get(j).equals(matr.get(i).get(j + 1))) {
                j_state = pair;
            }
            else {
                j_state = new Pair(i, j);
            }
        } else {
            j_state = new Pair(i, j);
        }

        if (i + 1 < matr.size()) {
            Pair pair = Func(i + 1, j, matr, treeMap);
            if (matr.get(i).get(j).equals(matr.get(i + 1).get(j))) {
                i_state = pair;
            }
            else {
                i_state = new Pair(i, j);
            }
        } else {
            i_state = new Pair(i, j);
        }

        if (!treeMap.containsKey(new Pair(1, 1))) {
            treeMap.put(new Pair(1, 1), new HashSet<>());
        }
        treeMap.get(new Pair(1, 1)).add(matr.get(i).get(j));

        if (i_state.compareTo(new Pair(i, j)) == 0 && j_state.i == i) {
            i_state = j_state;
        }
        else if (j_state.compareTo(new Pair(i, j)) == 0 && i_state.j == j) {
            j_state = i_state;
        }

        Pair pair = new Pair(Math.min(i_state.i, j_state.i) - i + 1, Math.min(i_state.j, j_state.j) - j + 1);

        if (!treeMap.containsKey(pair)) {
            treeMap.put(pair, new HashSet<>());
        }
        treeMap.get(pair).add(matr.get(i).get(j));

        for (int i_1 = i; i_1 <= i_state.i; ++i_1) {
            if (matr.get(i).get(j).equals(matr.get(i_1).get(j))) {
                if (!treeMap.containsKey(new Pair(i_1 - i + 1, i_state.j - j + 1))) {
                    treeMap.put(new Pair(i_1 - i + 1, i_state.j - j + 1), new HashSet<>());
                }
                treeMap.get(new Pair(i_1 - i + 1, i_state.j - j + 1)).add(matr.get(i).get(j));
            }
            else break;
        }

        for (int j_1 = j; j_1 <= j_state.j; ++j_1) {
            if (matr.get(i).get(j).equals(matr.get(i).get(j_1))) {
                if (!treeMap.containsKey(new Pair(j_state.i - i + 1, j_1 - j + 1))) {
                    treeMap.put(new Pair(j_state.i - i + 1, j_1 - j + 1), new HashSet<>());
                }
                treeMap.get(new Pair(j_state.i - i + 1, j_1 - j + 1)).add(matr.get(i).get(j));
            }
            else break;
        }

        if (!i_state.equals(new Pair(i, j)) && !j_state.equals(new Pair(i, j))) {
            return new Pair(Math.min(i_state.i, j_state.i), Math.min(i_state.j, j_state.j));
        }
        else if (i_state.equals(new Pair(i, j))) {
            return new Pair(i, j_state.j);
        }
        else if (j_state.equals(new Pair(i, j))) {
            return new Pair(i_state.i, j);
        }
        else return new Pair(i, j);
    }
}