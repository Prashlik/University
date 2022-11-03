using System;
using System.Collections.Generic;
using System.Drawing;

namespace LabWork4
{
    internal class Element
    {
        private String name;
        private Bitmap image;

        public Element()
        {
            this.image = null;
            this.name = null;
        }

        public Element(Bitmap img, string name)
        {
            this.image = img;
            this.name = name;
        }

        public Element(Element element)
        {
            this.name = element.name;
            this.image = element.image;
        }

        public String Name { get { return name; } set { name = value; } }

        public Bitmap Image { get { return image; } set { image = value; } }

        public static bool operator !=(Element a, Element b)
        {
            return (a.image != b.image || a.name != b.name);
        }

        public static bool operator ==(Element a, Element b)
        {
            return (a.image == b.image && a.name == b.name);
        }

        public override bool Equals(object obj)
        {
            return obj is Element element &&
                   name == element.name &&
                   EqualityComparer<Image>.Default.Equals(image, element.image);
        }

        public override int GetHashCode()
        {
            int hashCode = -923009584;
            hashCode = hashCode * -1521134295 + EqualityComparer<string>.Default.GetHashCode(name);
            hashCode = hashCode * -1521134295 + EqualityComparer<Image>.Default.GetHashCode(image);
            return hashCode;
        }
    }
}
